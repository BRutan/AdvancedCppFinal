#include "IndexDispersion.hpp"

#pragma region IndexDispersionAttributes:
#pragma region Private Methods:
void IndexDispersionAttributes::_MakeAttributesConsistent()
{
	// Ensure that long/short attributes are set correctly:
	// (if long index, short constituents, vice versa), expiration and
	// settlement dates are all the same, risk free rate is all the same, 
	bool indexIsLong = this->_IsLong;
	double riskFree = std::dynamic_pointer_cast<OptionAttributes>(this->_IndexOption.Attributes())->RiskFreeRate();
	this->_IndexOption.Attributes_Mutable()->IsLong(this->_IsLong);
	bool compIsLong = !indexIsLong;
	for (auto &component : this->_ConstituentOptions)
	{
		component.second.first.Attributes_Mutable()->IsLong(compIsLong);
		std::dynamic_pointer_cast<OptionAttributes>(component.second.first.Attributes_Mutable())->ExpirationDate(this->_ExpirationDate);
		std::dynamic_pointer_cast<OptionAttributes>(component.second.first.Attributes_Mutable())->RiskFreeRate(riskFree);
		std::dynamic_pointer_cast<OptionAttributes>(component.second.first.Attributes_Mutable())->SettlementDate(this->_SettlementDate);
	}
}
void IndexDispersionAttributes::_SetAttributes()
{
	// Calculate net price of the portfolio.
	double netPrice = this->_IndexOption.Price();
	for (auto &component : this->_ConstituentOptions)
	{
		netPrice += component.second.first.Price() * component.second.second;
	}
	this->_Price = netPrice;
}
void IndexDispersionAttributes::_InitializeAttributes()
{
	if (this->_IndexOption.Attributes() == nullptr)
	{
		this->_IndexOption.Attributes_Mutable() = std::make_shared<OptionAttributes>(OptionAttributes());
	}
	for (auto component = this->_ConstituentOptions.begin(); component != this->_ConstituentOptions.end();
		++component)
	{
		if (component->second.first.Attributes() == nullptr)
		{
			component->second.first.Attributes_Mutable() = std::make_shared<OptionAttributes>(OptionAttributes());
		}
	}
}
#pragma endregion
#pragma region Constructors/Destructor:
IndexDispersionAttributes::IndexDispersionAttributes() : _IndexName(), _IndexOption(), _ConstituentOptions(), DerivativeAttributes()
{
	this->_InitializeAttributes();
}
IndexDispersionAttributes::IndexDispersionAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions, const QuantLib::Date &settle, const QuantLib::Date &exp) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), DerivativeAttributes(0, isLong, settle, exp)
{
	this->_InitializeAttributes();
	this->_IndexOption.Attributes_Mutable()->IsLong(isLong);
	this->_MakeAttributesConsistent();
}
IndexDispersionAttributes::IndexDispersionAttributes(const IndexDispersionAttributes &attr) : _IndexName(attr._IndexName),
	_IndexOption(attr._IndexOption), _ConstituentOptions(attr._ConstituentOptions), DerivativeAttributes(attr)
{
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
	this->_SetAttributes();
}
IndexDispersionAttributes::~IndexDispersionAttributes()
{

}
#pragma endregion
#pragma region Accessors
const QuantLib::Date& IndexDispersionAttributes::ExpirationDate() const
{
	return this->_ExpirationDate;
}
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
double IndexDispersionAttributes::RiskfreeRate() const
{
	return std::dynamic_pointer_cast<OptionAttributes>(this->_IndexOption.Attributes())->RiskFreeRate();
}
const QuantLib::Date& IndexDispersionAttributes::SettlementDate() const
{
	return this->_SettlementDate;
}
#pragma endregion
#pragma region Mutators
void IndexDispersionAttributes::ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>> &constits)
{
	this->_ConstituentOptions = constits;
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
}
void IndexDispersionAttributes::ExpirationDate(const QuantLib::Date& dt)
{
	this->_ExpirationDate = dt;
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
}
void IndexDispersionAttributes::IndexName(const std::string& indexName)
{
	this->_IndexName = indexName;
}
void IndexDispersionAttributes::IndexOption(const Option& indexOpt)
{
	this->_IndexOption = indexOpt;
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
}
void IndexDispersionAttributes::RiskFreeRate(double rate)
{
	std::dynamic_pointer_cast<OptionAttributes>(this->_IndexOption.Attributes())->RiskFreeRate(rate);
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
}
void IndexDispersionAttributes::SettlementDate(const QuantLib::Date &dt)
{
	this->_SettlementDate = dt;
	this->_InitializeAttributes();
	this->_MakeAttributesConsistent();
}
void IndexDispersionAttributes::Generate()
{
	this->_IndexOption.Generate();
	for (auto component : this->_ConstituentOptions)
	{
		component.second.first.Generate();
	}
	this->_SetAttributes();
}
Option& IndexDispersionAttributes::IndexOption_Mutable()
{
	return this->_IndexOption;
}
void IndexDispersionAttributes::IsLong(bool isLong)
{
	this->_IsLong = isLong;
	this->_InitializeAttributes();
	this->_SetAttributes();
}
std::unordered_map<std::string, std::pair<Option, double>>& IndexDispersionAttributes::ConstituentOptions_Mutable()
{
	return this->_ConstituentOptions;
}
#pragma endregion
#pragma region Interface Methods
double IndexDispersionAttributes::ApproxExerciseDelta(double futurePrice, double iv, double tenor, double strike)
{
	return std::log(strike / futurePrice) / (iv * std::sqrt(tenor)) + .5 * iv * std::sqrt(tenor);
}
double IndexDispersionAttributes::TargetStrike(double futurePrice, double iv, double tenor, double x)
{
	return futurePrice * std::exp(iv * x * std::sqrt(tenor) - .5 * iv * iv *tenor);
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
IndexDispersion::IndexDispersion() : Derivative(std::make_shared<IndexDispersionAttributes>(IndexDispersionAttributes()))
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
PNLFileRow IndexDispersion::operator-(const IndexDispersion &disp)
{
	PNLFileRow row;
	row.Price(disp.Price());
	row.PriceChg(disp.Price() - this->Price());
	row.PercentChg(row.PriceChg() / disp.Price());
	row.ValueDate(disp.Attributes()->SettlementDate());
	row.Ticker(disp.IndexName());
	row.ImpliedCorrelation(disp.ImpliedCorrelation());
	row.Delta(disp.Delta());
	row.Gamma(disp.Gamma());
	row.Rho(disp.Rho());
	row.Theta(disp.Theta());
	row.Vega(disp.Vega());
	
	return row;
}
#pragma endregion
#pragma endregion