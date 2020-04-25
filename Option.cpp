#include "Option.hpp"


////////////////////
// OptionAttributes definitions:
////////////////////
// Constructors/Destructor:
OptionAttributes::OptionAttributes() : _IsCall(false), SecurityAttributes(), _Strike(0), _Price(0), _ImpliedVol(0), _TTM(0),
	_DivYield(0)
{

}
OptionAttributes::OptionAttributes(bool isCall, bool isLong, double tenor, double divYield, const OptionChainRow& row) : 
	_IsCall(isCall), SecurityAttributes(isLong), _Strike(row.Strike()), _Price((isLong) ? row.Ask() : row.Bid()), 
	_ImpliedVol(row.ImpliedVol()), _TTM(tenor), _DivYield(divYield)
{

}
OptionAttributes::~OptionAttributes()
{

}
// Accessors:
double OptionAttributes::DividendYield() const
{
	return this->_DivYield;
}
double OptionAttributes::Strike() const
{
	return this->_Strike;
}
double OptionAttributes::Price() const
{
	return this->_Price;
}
double OptionAttributes::ImpliedVol() const
{
	return this->_ImpliedVol;
}
double OptionAttributes::TimeToMaturity() const
{
	return this->_TTM;
}
bool OptionAttributes::IsCall() const
{
	return this->_IsCall;
}
// Mutators:
void OptionAttributes::DividendYield(double yield)
{
	this->_DivYield = yield;
}
void OptionAttributes::Strike(double strike)
{
	this->_Strike = strike;
}
void OptionAttributes::Price(double price)
{
	this->_Price = price;
}
void OptionAttributes::ImpliedVol(double iv)
{
	this->_ImpliedVol = iv;
}
void OptionAttributes::TimeToMaturity(double ttm)
{
	this->_TTM = ttm;
}
void OptionAttributes::IsCall(bool isCall)
{
	this->_IsCall = isCall;
}
// Overloaded Operators:
OptionAttributes& OptionAttributes::operator=(const OptionAttributes &attr)
{
	if (this != &attr)
	{
		this->_DivYield = attr._DivYield;
		this->_ImpliedVol = attr._ImpliedVol;
		this->_IsCall = attr._IsCall;
		this->_Long = attr._Long;
		this->_Price = attr._Price;
		this->_Strike = attr._Strike;
		this->_TTM = attr._TTM;
	}
	return *this;
}
////////////////////
// Option definitions:
////////////////////
// Constructors/Destructor:
Option::Option() : Derivative()
{

}
Option::Option(const OptionAttributes& attr) : Derivative(std::make_shared<OptionAttributes>(attr))
{

}
Option::~Option()
{

}
// Accessors:
double Option::Price() const
{
	return dynamic_cast<OptionAttributes*>(this->Attributes().get())->Price();
}
double Option::Price(const std::shared_ptr<SecurityAttributes>& attr) const
{
	return 0;
}
// Interface Functions:
double Option::ImpliedVolatility(const OptionAttributes &attr, double tol_approx, double tol_consec)
{
	// Compute implied volatility based on other parameters in OptionAttributes:
	return 0;
}
double Option::Delta() const
{
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());
	if (attr->IsCall())
	{

	}
	else
	{

	}
	return 0;
}
double Option::Gamma() const
{
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());
	double gamma = 0;
	if (attr->IsCall())
	{

	}
	else
	{

	}
	return gamma;
}
double Option::Theta() const
{
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());
	double theta = 0;
	if (attr->IsCall())
	{

	}
	else
	{

	}
	return theta;
}
double Option::Vega() const
{
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());
	double vega = 0;
	if (attr->IsCall())
	{

	}
	else
	{

	}
	return vega;
}
double Option::Rho() const
{
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());
	double rho = 0;
	if (attr->IsCall())
	{

	}
	else
	{

	}
	return rho;
}
// Static Methods:
double Option::Delta(const OptionAttributes& attrs)
{
	double delta = 0;
	if (attrs.IsCall())
	{

	}
	else
	{

	}
	return delta;
}
double Option::Gamma(const OptionAttributes& attrs)
{
	double gamma = 0;
	if (attrs.IsCall())
	{

	}
	else
	{

	}
	return gamma;
}
double Option::Theta(const OptionAttributes& attrs)
{
	double theta = 0;
	if (attrs.IsCall())
	{

	}
	else
	{

	}
	return theta;
}
double Option::Vega(const OptionAttributes& attrs)
{
	double vega = 0;
	if (attrs.IsCall())
	{

	}
	else
	{

	}
	return vega;
}
double Option::Rho(const OptionAttributes& attrs)
{
	double rho = 0;
	if (attrs.IsCall())
	{

	}
	else
	{

	}
	return rho;
}
// Overloaded Operators:
Option& Option::operator=(const Option &opt) 
{
	if (this != &opt)
	{
		this->_Attributes = opt._Attributes;
	}
	return *this;
}