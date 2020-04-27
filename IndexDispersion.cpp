#include "IndexDispersion.hpp"

#pragma region IndexDispersionAttributes:
#pragma region Private Methods:
void IndexDispersionAttributes::_SetAttributes()
{
	// Ensure that long/short attributes are set correctly:
	// (if long index, short constituents, vice versa).
	// Calculate net price of the portfolio.
	bool indexIsLong = this->_IndexOption.Attributes().IsLong();
	bool constIsLong = !indexIsLong;
	auto attr = static_cast<OptionAttributes&>(this->_IndexOption.Attributes());
	double netPrice = this->_IndexOption.Price();
	for (auto &pair : this->_ConstituentOptions)
	{
		static_cast<OptionAttributes&>(pair.second.first.Attributes()).IsLong(constIsLong);
		netPrice += pair.second.first.Price() * pair.second.second;
	}
	this->_Price = netPrice;
}
#pragma endregion
#pragma region Constructors/Destructor:
IndexDispersionAttributes::IndexDispersionAttributes() : _IndexName(), _IndexOption(), _ConstituentOptions(), DerivativeAttributes()
{

}
IndexDispersionAttributes::IndexDispersionAttributes(bool isLong, const std::string& indexName, Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions, const QuantLib::Date &settle, const QuantLib::Date &exp) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), DerivativeAttributes(0, isLong, settle, exp)
{
	this->_IndexOption.Attributes().IsLong(isLong);
	this->_SetAttributes();
}
IndexDispersionAttributes::IndexDispersionAttributes(IndexDispersionAttributes &attr) : _IndexName(attr._IndexName),
	_IndexOption(attr._IndexOption), _ConstituentOptions(attr._ConstituentOptions), DerivativeAttributes(attr)
{
	this->_SetAttributes();
}
IndexDispersionAttributes::IndexDispersionAttributes(IndexDispersionAttributes&& attr) : _IndexName(std::move(attr._IndexName)),
	_IndexOption(std::move(attr._IndexOption)), _ConstituentOptions(std::move(attr._ConstituentOptions)), DerivativeAttributes(std::move(attr))
{

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
Option& IndexDispersionAttributes::IndexOption()
{
	return this->_IndexOption;
}
std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersionAttributes::ConstituentOptions()
{
	return this->_ConstituentOptions;
}
#pragma endregion
#pragma region Mutators
void IndexDispersionAttributes::ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>> &constits)
{
	this->_ConstituentOptions = constits;
	this->_SetAttributes();
}
void IndexDispersionAttributes::IndexName(const std::string& indexName)
{
	this->_IndexName = indexName;
}
void IndexDispersionAttributes::IndexOption(const Option& indexOpt)
{
	this->_IndexOption = indexOpt;
	this->_SetAttributes();
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
IndexDispersion::IndexDispersion(IndexDispersionAttributes &attr) : 
	Derivative(attr)
{

}
IndexDispersion::IndexDispersion(IndexDispersion& trade) : Derivative(trade)
{

}
IndexDispersion::~IndexDispersion()
{

}
#pragma endregion
#pragma region Accessors
std::string& IndexDispersion::IndexName()
{
	return static_cast<IndexDispersionAttributes&>(this->Attributes()).IndexName();
}
Option& IndexDispersion::IndexOption()
{
	return static_cast<IndexDispersionAttributes&>(this->Attributes()).IndexOption();
}
std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersion::ConstitutentOptions()
{
	return static_cast<IndexDispersionAttributes&>(this->Attributes()).ConstituentOptions();
}
#pragma endregion
#pragma region Interface Methods
std::pair<IndexDispersion, double> IndexDispersion::OptimalDispersionTrade(const OptionChainPathGenerator &gen, IndexDispersionAttributes &attrs)
{
	OptionChains allchains(gen);
	auto indexChain = allchains.GetOptionChain(attrs.IndexName());
	auto chains = allchains.GetOptionChains();
	bool isNegative = false;
	double maxAbsImpCorr = 0, currImpCorr = 0;
	for (auto &row : indexChain->Data())
	{
		auto converted = dynamic_cast<OptionChainRow*>(row.second);
		currImpCorr = 0;
		for (auto &constituentChain : attrs.ConstituentOptions())
		{
			currImpCorr += 0;
		}
		if (std::abs(currImpCorr) > maxAbsImpCorr)
		{
			maxAbsImpCorr = std::abs(currImpCorr);
			bool isLong = currImpCorr < 0;
		}
	}
	// Generate trade using optimal strikes:
	IndexDispersion trade(attrs);
	return std::make_pair(trade, maxAbsImpCorr);
}
double IndexDispersion::ImpliedCorrelation(IndexDispersionAttributes &attr)
{
	std::size_t index = 0;
	double numerator = 0, denominator = 0;
	double curr_risk_entry = 0, sub_risk_entry = 0, iv = 0;
	for (auto &entry : attr.ConstituentOptions())
	{
		iv = static_cast<const OptionAttributes&>(entry.second.first.Attributes()).ImpliedVol();
		curr_risk_entry = entry.second.second * iv;
		numerator += curr_risk_entry * curr_risk_entry;
		std::size_t sub_index = 0;
		for (auto &sub_entry : attr.ConstituentOptions())
		{
			if (sub_index > index)
			{
				iv = static_cast<const OptionAttributes&>(sub_entry.second.first.Attributes()).ImpliedVol();
				sub_risk_entry = sub_entry.second.second * iv;
				denominator += curr_risk_entry * sub_risk_entry;
			}
			++sub_index;
		}
		++index;
	}
	double indexiv = static_cast<const OptionAttributes&>(attr.IndexOption().Attributes()).ImpliedVol();
	return (indexiv * indexiv - numerator) / denominator;
}
double IndexDispersion::Price() const
{
	return this->_Attributes.Price();
}
double IndexDispersion::Delta() const
{
	auto attr = static_cast<IndexDispersionAttributes&>(this->_Attributes);
	double delta = attr.IndexOption().Delta();
	for (auto &constituent : attr.ConstituentOptions())
	{
		delta += constituent.second.first.Delta() * constituent.second.second;
	}
	return delta;
}
double IndexDispersion::Gamma() const
{
	auto attr = static_cast<IndexDispersionAttributes&>(this->_Attributes);
	double gamma = attr.IndexOption().Gamma();
	for (auto &constituent : attr.ConstituentOptions())
	{
		gamma += constituent.second.first.Gamma() * constituent.second.second;
	}
	return gamma;
}
double IndexDispersion::Theta() const
{
	auto attr = static_cast<IndexDispersionAttributes&>(this->_Attributes);
	double theta = attr.IndexOption().Gamma();
	for (auto &constituent : attr.ConstituentOptions())
	{
		theta += constituent.second.first.Theta() * constituent.second.second;
	}
	return theta;
}
double IndexDispersion::Vega() const
{
	auto attr = static_cast<IndexDispersionAttributes&>(this->_Attributes);
	double vega = attr.IndexOption().Vega();
	for (auto &constituent : attr.ConstituentOptions())
	{
		vega += constituent.second.first.Vega() * constituent.second.second;
	}
	return vega;
}
double IndexDispersion::Rho() const
{
	auto attr = static_cast<IndexDispersionAttributes&>(this->_Attributes);
	double rho = attr.IndexOption().Rho();
	for (auto &constituent : attr.ConstituentOptions())
	{
		rho += constituent.second.first.Rho() * constituent.second.second;
	}
	return rho;
}
double IndexDispersion::ImpliedCorrelation() const
{
	return IndexDispersion::ImpliedCorrelation(static_cast<IndexDispersionAttributes&>(this->_Attributes));
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