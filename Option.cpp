#include "Option.hpp"


// Constructors/Destructor:
OptionAttributes::OptionAttributes(bool isCall, bool isLong, const OptionChainRow& row) : _IsCall(isCall), SecurityAttributes(isLong),
	_Strike(row.Strike()), _Price((isLong) ? row.Ask() : row.Bid()), _ImpliedVol(row.ImpliedVol()), _TTM(row.TimeToMaturity()) 
{

}
OptionAttributes::~OptionAttributes()
{

}
// Accessors:
double OptionAttributes::Strike() const
{

}
double OptionAttributes::Price() const
{

}
double OptionAttributes::ImpliedVol() const
{

}
double OptionAttributes::TimeToMaturity() const
{

}
bool OptionAttributes::IsCall() const
{

}
// Mutators:
void OptionAttributes::Strike(double)
{

}
void OptionAttributes::Price(double)
{

}
void OptionAttributes::ImpliedVol(double)
{

}
void OptionAttributes::TimeToMaturity(double)
{

}
void OptionAttributes::IsCall(bool)
{

}
// Overloaded Operators:
OptionAttributes& OptionAttributes::operator=(const OptionAttributes&)
{

}

Option::Option(const OptionAttributes& attr)
{

}
Option::Option(bool isCall, bool isLong, const OptionChainRow& row)
{

}
Option::~Option()
{

}
// Accessors:
double Option::Price()
{
	return ((const OptionAttributes*)this->Attributes())->Price();
}
double Option::Price(const SecurityAttributes* attr)
{
	OptionAttributes * optAttr = (OptionAttributes*)attr;
}
// Interface Functions:
double Option::BlackScholesValuation(const OptionAttributes &attr)
{

}
double Option::ImpliedVolatility(const OptionAttributes &attr)
{

}
// Overloaded Operators:
Option& Option::operator=(const Option &opt) 
{
	if (this != &opt)
	{
		this->_
	}
	return *this;
}