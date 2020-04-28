#include "AssetFactory.hpp"

// Constructors/Destructor:
AssetFactory::AssetFactory() : _GenerateLong(), _RiskFreeCurve(), _Settle(), _Expiry()
{

}
AssetFactory::AssetFactory(bool generateLong, const ZeroCurve& curve, const QuantLib::Date &settle, const QuantLib::Date &expiry) :
	_GenerateLong(generateLong), _RiskFreeCurve(curve), _Settle(settle), _Expiry(expiry)
{

}
AssetFactory::AssetFactory(const AssetFactory &gen) : _GenerateLong(gen._GenerateLong), _RiskFreeCurve(gen._RiskFreeCurve),
_Settle(gen._Settle), _Expiry(gen._Expiry)
{

}
AssetFactory::~AssetFactory()
{

}
// Accessors:
bool AssetFactory::GeneratingLong() const
{
	return this->_GenerateLong;
}

const ZeroCurve& AssetFactory::RiskFreeCurve() const
{
	return this->_RiskFreeCurve;
}
const QuantLib::Date& AssetFactory::Settlement() const
{
	return this->_Settle;
}
const QuantLib::Date& AssetFactory::Expiration() const
{
	return this->_Expiry;
}
// Mutators:
void AssetFactory::Expiration(const QuantLib::Date &dt)
{
	this->_Expiry = dt;
}
void AssetFactory::GeneratingLong(bool genLong)
{
	this->_GenerateLong = genLong;
}
void AssetFactory::RiskFree(const ZeroCurve& riskfree)
{
	this->_RiskFreeCurve = riskfree;
}
void AssetFactory::Settlement(const QuantLib::Date &dt)
{
	this->_Settle = dt;
}
// Interface Methods:
Option AssetFactory::GenerateOption(bool isCall, const OptionChainRow &data, const EquityAttributes &underlying) const
{
	// Find closes risk free rate to expiration:
	double rate = this->_RiskFreeCurve.ZeroRate(this->_Settle, this->_Expiry);
	double premium = (this->_GenerateLong) ? data.Ask() : data.Bid();
	OptionAttributes attr(isCall, this->_GenerateLong, premium, rate, 
		data, this->_Settle, this->_Expiry, underlying);
	return Option(attr);
}
IndexDispersionAttributes AssetFactory::GenerateDispersionAttributes(const std::string &indexSymbol, const ComponentWeightsFile& weights,
	const std::unordered_map<std::string,EquityAttributes>& underlyings) const
{
	// Generate empty IndexDisperionAttributes object:
	auto indexUnderlying = underlyings.find(indexSymbol);
	if (indexUnderlying == underlyings.end())
	{
		throw std::exception("Missing index underlying info.");
	}
	IndexDispersionAttributes attr;
	std::unordered_map<std::string, std::pair<Option, double>> comps;
	std::pair<Option, double> curr_const;
	attr.IndexName(indexSymbol);
	attr.IsLong(this->_GenerateLong);
	attr.SettlementDate(this->_Settle);
	attr.ExpirationDate(this->_Expiry);
	// Generate all options associated with index and trade:
	for (auto &elem : weights.Tickers())
	{
		auto underlying = underlyings.find(elem.second.Ticker());
		if (underlying == underlyings.end())
		{
			throw std::exception("Missing one or more tickers from underlyings.");
		}
		auto newOpt = new OptionAttributes();
		newOpt->IsLong(!this->_GenerateLong);
		curr_const = std::make_pair<Option, double>(*newOpt, elem.second.Weight());
		comps.emplace(elem.second.Ticker(), curr_const);
	}
	// Add all constituent options:
	attr.ConstituentOptions(comps);
	return attr;
}
IndexDispersion AssetFactory::GenerateDispersion(const std::string &indexSymbol, double indexStrike, const ComponentWeightsFile& weights, const OptionChains& chains,
	const std::unordered_map<std::string, EquityAttributes>& underlyings) const
{
	auto indexUnderlying = underlyings.find(indexSymbol);
	if (!chains.HasOptionChain(indexSymbol))
	{
		throw std::exception("Index not present in option chains.");
	}
	if (indexUnderlying == underlyings.end())
	{
		throw std::exception("Missing index underlying info.");
	}
	auto indexChain = chains.GetOptionChain(indexSymbol);
	OptionChainRow row;
	if (!indexChain->HasStrike(indexStrike))
	{
		indexStrike = indexChain->GetClosestStrike(indexStrike);
		row = indexChain->GetRow(indexStrike);
	}
	else
	{
		row = indexChain->GetRow(indexStrike);
	}
	IndexDispersionAttributes attr;
	std::unordered_map<std::string, std::pair<Option, double>> comps;
	std::pair<Option, double> curr_const;
	attr.IndexOption(this->GenerateOption(this->_GenerateLong, row, indexUnderlying->second));
	attr.IndexName(indexSymbol);
	attr.IsLong(this->_GenerateLong);
	attr.SettlementDate(this->_Settle);
	attr.ExpirationDate(this->_Expiry);
	// Generate all options associated with index and trade:
	for (auto &elem : weights.Tickers())
	{
		auto chain = chains.GetOptionChain(elem.second.Ticker());
		auto underlying = underlyings.find(elem.second.Ticker());
		if (underlying == underlyings.end())
		{
			throw std::exception("Missing one or more tickers from underlyings.");
		}
		auto component_strike = indexStrike / elem.second.Weight();
		if (!chain->HasStrike(component_strike))
		{
			component_strike = chain->GetClosestStrike(component_strike);
		}
		curr_const = std::make_pair<Option, double>(
			this->GenerateOption(!this->_GenerateLong, chain->GetRow(component_strike), underlying->second),
			elem.second.Weight());
		comps.emplace(elem.second.Ticker(), curr_const);
	}
	// Add all constituent options:
	attr.ConstituentOptions(comps);
	return IndexDispersion(attr);
}
IndexDispersion AssetFactory::OptimalDispersionTrade(const OptionChainPathGenerator &gen,
	const IndexDispersionAttributes &attrs, const std::unordered_map<std::string, EquityAttributes>& underlyings, double assumedIV)
{
	// Get all option chains:
	OptionChains allchains(gen);
	auto indexChain = allchains.GetOptionChain(attrs.IndexName());
	auto chains = allchains.GetOptionChains();
	IndexDispersionAttributes out, copy(attrs);
	double riskFree = this->_RiskFreeCurve.ZeroRate(gen.ValueDate(), gen.ExpirationDate());
	double tenor = ZeroCurve::Tenor(gen.ValueDate(), gen.ExpirationDate());
	if (copy.IndexOption_Mutable().Attributes_Mutable() == nullptr)
	{
		copy.IndexOption_Mutable().Attributes_Mutable() = 
			std::make_shared<OptionAttributes>(OptionAttributes());
	}
	// For each index strike, determine approx equal delta strikes, and determine implied correlation.
	// Find combination that has highest implied correlation:
	auto indexPrice = underlyings.find(attrs.IndexName())->second.Price();
	auto indexDiv = underlyings.find(attrs.IndexName())->second.DividendYield();
	auto indexFuture = indexPrice * std::exp((riskFree - indexDiv) * tenor);
	bool isNegative = false;
	double maxAbsImpCorr = 0, impCorr, delta;
	for (auto &indexRow : indexChain->Data())
	{
		auto converted = dynamic_cast<OptionChainRow*>(indexRow.second);
		auto indexStrike = converted->Strike();
		auto indexIV = converted->ImpliedVol();
		auto indexApproxDelta = IndexDispersionAttributes::ApproxExerciseDelta(indexFuture, indexIV, tenor, indexStrike);
		dynamic_cast<OptionAttributes*>(copy.IndexOption_Mutable().Attributes_Mutable().get())->Strike(indexStrike);
		dynamic_cast<OptionAttributes*>(copy.IndexOption_Mutable().Attributes_Mutable().get())->ImpliedVol(indexIV);
		std::vector<double> deltas{ indexApproxDelta };
		for (auto component = copy.ConstituentOptions_Mutable().begin();
			component != copy.ConstituentOptions_Mutable().end(); ++component)
		{
			if (component->first == attrs.IndexName())
			{
				continue;
			}
			if (component->second.first.Attributes_Mutable() == nullptr)
			{
				component->second.first.Attributes_Mutable() = std::make_shared<OptionAttributes>(OptionAttributes());
			}
			auto chain = allchains.GetOptionChain(component->first);
			auto equityAttr = underlyings.find(component->first)->second;
			auto futurePrice = equityAttr.Price() * std::exp((riskFree - equityAttr.DividendYield()) * tenor);
			auto targetStrike = IndexDispersionAttributes::TargetStrike(futurePrice, indexIV, tenor, indexApproxDelta);
			auto targetStrike = dynamic_cast<OptionChain*>(chains[component->first])->GetClosestStrike(targetStrike);
			if (targetStrike < 0 || targetStrike >= indexStrike)
			{
				// Use estimated implied volatility and compute price using model if price not available:
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Strike(equityAttr.Price());
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->ImpliedVol(assumedIV);
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Price(0);
			}
			else
			{
				auto row = dynamic_cast<OptionChain*>(chains[component->first])->GetRow(comp_strike);
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Strike(comp_strike);
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->ImpliedVol(row.ImpliedVol());
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Price(row.Bid());
			}
		}
		// Get implied correlation:
		impCorr = IndexDispersion::ImpliedCorrelation(copy);
		if (std::abs(impCorr) > maxAbsImpCorr)
		{
			out = copy;
			maxAbsImpCorr = std::abs(impCorr);
			isNegative = impCorr < 0;
		}
	}
	// Generate trade using optimal strikes:
	out.IsLong(isNegative);
	out.ExpirationDate(gen.ExpirationDate());
	out.SettlementDate(gen.ValueDate());
	out.RiskFreeRate(riskFree);
	// Set all underlying attributes:
	dynamic_cast<OptionAttributes*>(
		out.IndexOption_Mutable().Attributes_Mutable().get())->Underlying(underlyings.find(out.IndexName())->second);
	for (auto component = out.ConstituentOptions_Mutable().begin(); component != out.ConstituentOptions_Mutable().end();
		++component)
	{
		dynamic_cast<OptionAttributes*>(
			component->second.first.Attributes_Mutable().get())->Underlying(underlyings.find(component->first)->second);
	}
	out.Generate();
	return IndexDispersion(out);
}
// Overloaded Operators:
AssetFactory& AssetFactory::operator=(const AssetFactory &tg)
{
	if (this != &tg)
	{
		this->_Expiry = tg._Expiry;
		this->_GenerateLong = tg._GenerateLong;
		this->_RiskFreeCurve = tg._RiskFreeCurve;
		this->_Settle = tg._Settle;
	}
	return *this;
}