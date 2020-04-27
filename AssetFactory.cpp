#include "AssetFactory.hpp"

// Private Methods:
double AssetFactory::_ClosestRiskFreeRate(const QuantLib::Date& exp) const
{
	return 0;
}
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
	double rate = this->_ClosestRiskFreeRate(this->_Expiry);
	double premium = (this->_GenerateLong) ? data.Ask() : data.Bid();
	OptionAttributes attr(isCall, this->_GenerateLong, premium, rate, underlying.DividendYield(),
		underlying.Price(), data, this->_Settle, this->_Expiry);
	return Option(attr);
}
IndexDispersionAttributes AssetFactory::GenerateDisperionAttributes(const std::string &indexSymbol, const ComponentWeightsFile& weights,
	const std::unordered_map<std::string, EquityAttributes>& underlyings) const
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
		auto newOpt = std::make_shared<OptionAttributes>(OptionAttributes());
		newOpt->IsLong(!this->_GenerateLong);
		curr_const = std::make_pair<Option, double>(Option(newOpt), elem.second.Weight());
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
