#include "IndexDispersion.hpp"

#pragma region IndexDispersionAttributes:
#pragma region Private Methods:
void IndexDispersionAttributes::_SetAttributes()
{
	// Ensure that long/short attributes are set correctly:
	// (if long index, short constituents, vice versa).
	// Calculate net price of the portfolio.
	bool indexIsLong = this->_IndexOption.Attributes()->IsLong();
	bool constIsLong = !indexIsLong;
	auto attr = dynamic_cast<OptionAttributes*>(this->_IndexOption.Attributes().get());
	attr->IsLong(indexIsLong);
	const std::shared_ptr<OptionAttributes> ptr(attr);
	this->_IndexOption.SetAttributes(ptr);
	double netPrice = this->_IndexOption.Price();
	for (auto &pair : this->_ConstituentOptions)
	{
		auto attr = dynamic_cast<OptionAttributes*>(pair.second.first.Attributes().get());
		attr->IsLong(constIsLong);
		const std::shared_ptr<OptionAttributes> ptr(attr);
		pair.second.first.SetAttributes(ptr);
		netPrice += pair.second.first.Price() * pair.second.second;
	}
	this->_Price = netPrice;
}
#pragma endregion
#pragma region Constructors/Destructor:
IndexDispersionAttributes::IndexDispersionAttributes() : _IndexName(), _IndexOption(), _ConstituentOptions(), DerivativeAttributes()
{

}
IndexDispersionAttributes::IndexDispersionAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions, const QuantLib::Date &settle, const QuantLib::Date &exp) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), DerivativeAttributes(0, isLong, settle, exp)
{
	this->_IndexOption.Attributes()->IsLong(isLong);
	// Ensure attributes set correctly, calculate initial NPV:
	this->_SetAttributes();
}
IndexDispersionAttributes::IndexDispersionAttributes(const IndexDispersionAttributes &attr) : _IndexName(attr._IndexName),
	_IndexOption(attr._IndexOption), _ConstituentOptions(attr._ConstituentOptions), DerivativeAttributes(attr)
{
	if (this->_IndexOption.Attributes() != nullptr)
	{
		this->_SetAttributes();
	}
}
IndexDispersionAttributes::~IndexDispersionAttributes()
{

}
#pragma endregion
#pragma region Accessors
const std::string& IndexDispersionAttributes::IndexName() const
{
	return this->_IndexName;
}
const Option& IndexDispersionAttributes::IndexOption() const
{
	return this->_IndexOption;
}
const std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersionAttributes::ConstituentOptions() const
{
	return this->_ConstituentOptions;
}
#pragma endregion
#pragma region Mutators
void IndexDispersionAttributes::ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>> &constits)
{
	this->_ConstituentOptions = constits;
	// Ensure attributes set correctly:
	if (this->_IndexOption.Attributes() != nullptr)
	{
		this->_SetAttributes();
	}
}
void IndexDispersionAttributes::IndexName(const std::string& indexName)
{
	this->_IndexName = indexName;
}
void IndexDispersionAttributes::IndexOption(const Option& indexOpt)
{
	this->_IndexOption = indexOpt;
	if (this->_ConstituentOptions.size())
	{
		this->_SetAttributes();
	}
}
Option& IndexDispersionAttributes::IndexOption_Mutable()
{
	return this->_IndexOption;
}
std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersionAttributes::ConstituentOptions_Mutable()
{
	return this->_ConstituentOptions;
}
#pragma endregion
#pragma region Overloaded Operators
IndexDispersionAttributes& IndexDispersionAttributes::operator=(const IndexDispersionAttributes &attr)
{
	if (this != &attr)
	{
		this->_ConstituentOptions = attr._ConstituentOptions;
		this->_IndexName = attr._IndexName;
		this->_IndexOption = attr._IndexOption;
		SecurityAttributes::operator=(attr);
	}
	return *this;
}
#pragma endregion
#pragma endregion

#pragma region IndexDispersion
#pragma region Constructors/Destructor
IndexDispersion::IndexDispersion() : Derivative()
{

}
IndexDispersion::IndexDispersion(const IndexDispersionAttributes &attr) : 
	Derivative(std::make_shared<IndexDispersionAttributes>(attr))
{

}
IndexDispersion::IndexDispersion(const IndexDispersion& trade) : Derivative(trade)
{

}
IndexDispersion::~IndexDispersion()
{

}
#pragma endregion
#pragma region Accessors
const std::string& IndexDispersion::IndexName() const
{
	return dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get())->IndexName();
}
const Option& IndexDispersion::IndexOption() const
{
	return dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get())->IndexOption();
}
const std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersion::ConstitutentOptions() const
{
	return dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get())->ConstituentOptions();
}
#pragma endregion
#pragma region Interface Methods
std::pair<IndexDispersion, double> IndexDispersion::OptimalDispersionTrade(const OptionChainPathGenerator &gen, 
	const IndexDispersionAttributes &attrs, const std::unordered_map<std::string, EquityAttributes>& underlyings, double assumedIV)
{
	// Get all option chains:
	OptionChains allchains(gen);
	auto indexChain = allchains.GetOptionChain(attrs.IndexName());
	auto chains = allchains.GetOptionChains();
	IndexDispersionAttributes out, copy(attrs);
	bool isNegative = false;
	double maxAbsImpCorr = 0, impCorr;
	auto indexOpt = copy.IndexOption_Mutable();
	auto components = copy.ConstituentOptions_Mutable();
	if (indexOpt.Attributes_Mutable() == nullptr)
	{
		indexOpt.Attributes_Mutable() = std::make_shared<OptionAttributes>(OptionAttributes());
	}
	// Set attributes for to feed into ImpliedCorrelation():
	for (auto &indexRow : indexChain->Data())
	{
		auto converted = dynamic_cast<OptionChainRow*>(indexRow.second);
		auto indexStrike = converted->Strike();
		auto indexIV = converted->ImpliedVol();
		dynamic_cast<OptionAttributes*>(indexOpt.Attributes_Mutable().get())->Strike(indexStrike);
		dynamic_cast<OptionAttributes*>(indexOpt.Attributes_Mutable().get())->ImpliedVol(indexIV);
		for (auto component = components.begin(); component != components.end(); ++component)
		{
			if (component->first == attrs.IndexName())
			{
				continue;
			}
			if (component->second.first.Attributes_Mutable() == nullptr)
			{
				component->second.first.Attributes_Mutable() = std::make_shared<OptionAttributes>(OptionAttributes());
			}
			if (!(chains.find(component->first) != chains.end() && chains[component->first]->NumRows() != 0))
			{
			Assume:
				// Use estimated implied volatility and atm strike price:
				auto eqPrice = underlyings.find(component->first)->second.Price();
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Strike(eqPrice);
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->ImpliedVol(assumedIV);
			}
			else
			{
				auto weight = component->second.second;
				auto comp_strike = dynamic_cast<OptionChain*>(chains[component->first])->GetClosestStrike(indexStrike * weight);
				if (comp_strike < 0)
				{
					goto Assume;
				}
				auto comp_iv = dynamic_cast<OptionChain*>(chains[component->first])->GetRow(comp_strike).ImpliedVol();
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->Strike(comp_strike);
				dynamic_cast<OptionAttributes*>(component->second.first.Attributes_Mutable().get())->ImpliedVol(comp_iv);
			}
		}
		// Get implied correlation:
		impCorr = IndexDispersion::ImpliedCorrelation(copy);
		if (std::abs(impCorr) > maxAbsImpCorr)
		{
			maxAbsImpCorr = std::abs(impCorr);
			isNegative = impCorr < 0;
		}
	}
	// Generate trade using optimal strikes:
	IndexDispersion trade(copy);
	maxAbsImpCorr *= ((isNegative) ? -1 : 1);
	return std::make_pair(trade, maxAbsImpCorr);
}
double IndexDispersion::ImpliedCorrelation(const IndexDispersionAttributes &attr)
{
	double numerator = 0, denominator = 0;
	double curr_risk_entry, sub_risk_entry, iv = 0;
	for (auto &entry : attr.ConstituentOptions())
	{
		iv = dynamic_cast<OptionAttributes*>(entry.second.first.Attributes().get())->ImpliedVol();
		curr_risk_entry = entry.second.second * iv;
		numerator += curr_risk_entry * curr_risk_entry;
	}
	// Calculate denominator:
	std::size_t index = 0, sub_index;
	for (auto &entry : attr.ConstituentOptions())
	{
		iv = dynamic_cast<OptionAttributes*>(entry.second.first.Attributes().get())->ImpliedVol();
		curr_risk_entry = entry.second.second * iv;
		sub_index = 0;
		for (auto &sub_entry : attr.ConstituentOptions())
		{
			if (sub_index != index)
			{
				iv = dynamic_cast<OptionAttributes*>(sub_entry.second.first.Attributes().get())->ImpliedVol();
				sub_risk_entry = sub_entry.second.second * iv;
				denominator += curr_risk_entry * sub_risk_entry;
			}
			++sub_index;
		}
		++index;
	}
	double indexiv = dynamic_cast<OptionAttributes*>(attr.IndexOption().Attributes().get())->ImpliedVol();
	return (indexiv * indexiv - numerator) / denominator;
}
double IndexDispersion::Price() const
{
	return this->_Attributes->Price();
}
double IndexDispersion::Delta() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double delta = attr->IndexOption().Delta();
	for (auto &constituent : attr->ConstituentOptions())
	{
		delta += constituent.second.first.Delta() * constituent.second.second;
	}
	return delta;
}
double IndexDispersion::Gamma() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double gamma = attr->IndexOption().Gamma();
	for (auto &constituent : attr->ConstituentOptions())
	{
		gamma += constituent.second.first.Gamma() * constituent.second.second;
	}
	return gamma;
}
double IndexDispersion::Theta() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double theta = attr->IndexOption().Gamma();
	for (auto &constituent : attr->ConstituentOptions())
	{
		theta += constituent.second.first.Theta() * constituent.second.second;
	}
	return theta;
}
double IndexDispersion::Vega() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double vega = attr->IndexOption().Vega();
	for (auto &constituent : attr->ConstituentOptions())
	{
		vega += constituent.second.first.Vega() * constituent.second.second;
	}
	return vega;
}
double IndexDispersion::Rho() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double rho = attr->IndexOption().Rho();
	for (auto &constituent : attr->ConstituentOptions())
	{
		rho += constituent.second.first.Rho() * constituent.second.second;
	}
	return rho;
}
double IndexDispersion::ImpliedCorrelation() const
{
	return IndexDispersion::ImpliedCorrelation(*dynamic_cast<IndexDispersionAttributes*>(this->_Attributes.get()));
}
#pragma endregion
#pragma region Overloaded Operators
IndexDispersion& IndexDispersion::operator=(const IndexDispersion &trade)
{
	if (this != &trade)
	{
		Derivative::operator=(trade);
	}
	return *this;
}
#pragma endregion
#pragma endregion