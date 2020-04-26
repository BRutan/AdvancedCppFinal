#include "IndexDispersion.hpp"

#pragma region IndexDispersionAttributes:
#pragma region Private Methods:
void IndexDispersionAttributes::_SetAttributesCorrectly()
{
	// Ensure that long/short attributes are set correctly:
	// (if long index, short constituents, vice versa):
	bool indexIsLong = this->_IndexOption.Attributes()->IsLong();
	bool constIsLong = !indexIsLong;
	auto attr = dynamic_cast<OptionAttributes*>(this->_IndexOption.Attributes().get());
	attr->IsLong(indexIsLong);
	const std::shared_ptr<OptionAttributes> ptr(attr);
	this->_IndexOption.SetAttributes(ptr);
	for (auto &pair : this->_ConstituentOptions)
	{
		auto attr = dynamic_cast<OptionAttributes*>(pair.second.first.Attributes().get());
		attr->IsLong(constIsLong);
		const std::shared_ptr<OptionAttributes> ptr(attr);
		pair.second.first.SetAttributes(ptr);
	}
}
#pragma endregion
#pragma region Constructors/Destructor:
IndexDispersionAttributes::IndexDispersionAttributes() : _IndexName(), _IndexOption(), _ConstituentOptions(), DerivativeAttributes()
{

}
IndexDispersionAttributes::IndexDispersionAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions, const QuantLib::Date &settle, const QuantLib::Date &exp) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), DerivativeAttributes(isLong, settle, exp)
{
	this->_IndexOption.Attributes()->IsLong(isLong);
	// Ensure attributes set correctly:
	this->_SetAttributesCorrectly();
}
IndexDispersionAttributes::IndexDispersionAttributes(const IndexDispersionAttributes &attr) : _IndexName(attr._IndexName),
	_IndexOption(attr._IndexOption), _ConstituentOptions(attr._ConstituentOptions), DerivativeAttributes(attr)
{
	// Ensure attributes set correctly:
	this->_SetAttributesCorrectly();
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
	this->_SetAttributesCorrectly();
}
void IndexDispersionAttributes::IndexName(const std::string& indexName)
{
	this->_IndexName = indexName;
}
void IndexDispersionAttributes::IndexOption(const Option& indexOpt)
{
	this->_IndexOption = indexOpt;
	// Ensure attributes set correctly:
	this->_SetAttributesCorrectly();
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
IndexDispersion::IndexDispersion(const IndexDispersionAttributes &attr) : Derivative(std::make_shared<IndexDispersionAttributes>(attr))
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
std::pair<IndexDispersion, double> IndexDispersion::OptimalDispersionTrade(const OptionChainPathGenerator &gen, const IndexDispersionAttributes &attrs)
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
double IndexDispersion::ImpliedCorrelation(const IndexDispersionAttributes &attr)
{
	// Find the maximum absolute correlation:
	return 0;
}
double IndexDispersion::Price() const
{
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	double price = attr->IndexOption().Price();
	for (auto &constituent : attr->ConstituentOptions())
	{
		price += constituent.second.first.Price() * constituent.second.second;
	}
	return price;
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
	std::size_t index = 0;
	double numerator = 0, denominator = 0;
	double curr_risk_entry = 0, sub_risk_entry = 0, iv = 0;
	auto attr = dynamic_cast<IndexDispersionAttributes*>(this->Attributes().get());
	for (auto &entry : attr->ConstituentOptions())
	{
		iv = dynamic_cast<OptionAttributes*>(entry.second.first.Attributes().get())->ImpliedVol();
		curr_risk_entry = entry.second.second * iv;
		numerator += curr_risk_entry * curr_risk_entry;
		std::size_t sub_index = 0;
		for (auto &sub_entry : attr->ConstituentOptions())
		{
			if (sub_index > index)
			{
				iv = dynamic_cast<OptionAttributes*>(sub_entry.second.first.Attributes().get())->ImpliedVol();
				sub_risk_entry = sub_entry.second.second * iv;
				denominator += curr_risk_entry * sub_risk_entry;
			}
			++sub_index;
		}
		++index;
	}
	double indexCorr = dynamic_cast<OptionAttributes*>(attr->IndexOption().Attributes().get())->ImpliedVol();
	return (indexCorr - numerator) / denominator;
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