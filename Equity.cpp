#include "Equity.hpp"

// Constructors/Destructor:
EquityAttributes::EquityAttributes() : _MarginRate(0), _DividendYield(0), SecurityAttributes()
{

}
EquityAttributes::EquityAttributes(double price, const QuantLib::Date &settle, bool isLong, 
	double margin_rate, double dividendYield) : _MarginRate(margin_rate), _DividendYield(dividendYield),
	SecurityAttributes(price,settle,isLong)
{

}
EquityAttributes::EquityAttributes(const EquityAttributes& attr) : _MarginRate(attr._MarginRate), _DividendYield(attr._DividendYield)
{

}
// Accessors:
double EquityAttributes::MarginRate() const
{
	return this->_MarginRate;
}
double EquityAttributes::DividendYield() const
{
	return this->_DividendYield;
}
void EquityAttributes::MarginRate(double rate)
{
	this->_MarginRate = rate;
}
void EquityAttributes::DividendYield(double divyield)
{
	this->_DividendYield = divyield;
}
// Overloaded Operators:
EquityAttributes& EquityAttributes::operator=(const EquityAttributes &attr)
{
	if (this != &attr)
	{
		this->_DividendYield = attr._DividendYield;
		this->_MarginRate = attr._MarginRate;
		SecurityAttributes::operator=(attr);
	}
	return *this;
}


// Constructors/Destructor:
Equity::Equity() : Security()
{

}
Equity::Equity(EquityAttributes& attr) : Security(attr)
{

}
Equity::Equity(Equity& eq) : Security(eq)
{

}
Equity::~Equity()
{

}
// Accessors:
const std::shared_ptr<EquityAttributes>& Equity::GetAttributes() const
{
	return std::make_shared<EquityAttributes>(this->_Attributes.get());
}
// Mutators:
void Equity::SetAttributes(const EquityAttributes& attr)
{
	this->_Attributes = attr;
}
// Interface Methods:
double Equity::Delta() const
{
	return 1;
}
double Equity::Gamma() const
{
	return 0;
}
double Equity::Theta() const
{
	return 0;
}
double Equity::Vega() const
{
	return 0;
}
double Equity::Rho() const
{
	return 0;
}
// Overloaded Operator:
Equity& Equity::operator=(const Equity& eq)
{
	if (this != &eq)
	{
		Security::operator=(eq);
	}
	return *this;
}