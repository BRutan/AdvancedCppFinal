#include "Option.hpp"


////////////////////
// OptionAttributes definitions:
////////////////////
// Constructors/Destructor:
OptionAttributes::OptionAttributes() : _IsCall(), SecurityAttributes(), _Strike(), _Price(), _ImpliedVol()
{

}
OptionAttributes::OptionAttributes(bool isCall, bool isLong, double tenor, const OptionChainRow& row) : _IsCall(isCall), SecurityAttributes(isLong),
	_Strike(row.Strike()), _Price((isLong) ? row.Ask() : row.Bid()), _ImpliedVol(row.ImpliedVol()), _TTM(tenor) 
{

}
OptionAttributes::~OptionAttributes()
{

}
// Accessors:
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
Option::Option(const OptionAttributes& attr) : Derivative(&attr)
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
double Option::Price(const SecurityAttributes* attr) const
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
	return 0;
}
double Option::Gamma() const
{
	return 0;
}
double Option::Theta() const
{
	return 0;
}
double Option::Vega() const
{
	return 0;
}
double Option::Rho() const
{
	return 0;
}
static double Delta(const OptionAttributes& attrs)
{
	return 0;
}
static double Gamma(const OptionAttributes& attrs)
{
	return 0;
}
static double Theta(const OptionAttributes& attrs)
{
	return 0;
}
static double Vega(const OptionAttributes& attrs)
{
	return 0;
}
static double Rho(const OptionAttributes& attrs)
{
	return 0;
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