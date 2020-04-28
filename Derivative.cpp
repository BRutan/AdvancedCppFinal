#include "Derivative.hpp"

/////////////////////////
// DerivativeAttributes Definitions
/////////////////////////
DerivativeAttributes::DerivativeAttributes() : SecurityAttributes(), _ExpirationDate()
{

}
DerivativeAttributes::DerivativeAttributes(const DerivativeAttributes &attr) : 
	SecurityAttributes(attr._Price, attr._SettlementDate, attr._IsLong), _ExpirationDate(attr._ExpirationDate)
{

}
DerivativeAttributes::DerivativeAttributes(double price, bool isLong, const QuantLib::Date& settle, const QuantLib::Date& exp) : 
	SecurityAttributes(price,settle, isLong), _ExpirationDate(exp)
{
	
}
DerivativeAttributes::~DerivativeAttributes()
{

}
// Accessors:
const QuantLib::Date& DerivativeAttributes::ExpirationDate() const
{
	return this->_ExpirationDate;
}
// Mutators:
void DerivativeAttributes::ExpirationDate(const QuantLib::Date& dt)
{
	this->_ExpirationDate = dt;
}
// Interface Methods:
double DerivativeAttributes::TimeToMaturity() const
{
	return QuantLib::Actual365Fixed().yearFraction(this->_ExpirationDate, this->_SettlementDate);
}
// Overloaded Operators:
DerivativeAttributes& DerivativeAttributes::operator=(const DerivativeAttributes& attr)
{
	if (this != &attr)
	{
		this->_ExpirationDate = attr._ExpirationDate;
		SecurityAttributes::operator=(attr);
	}
	return *this;
}

/////////////////////////
// Derivative Definitions
/////////////////////////
// Constructors/Destructor:
Derivative::Derivative() : Security()
{

}
Derivative::Derivative(const std::shared_ptr<DerivativeAttributes>& attr) : Security(attr)
{

}
Derivative::Derivative(const Derivative& deriv) : Security()
{

}
Derivative::~Derivative()
{

}
// Overloaded Operators:
Derivative& Derivative::operator=(const Derivative& deriv)
{
	if (this != &deriv)
	{
		this->Attributes_Mutable()->IsLong(deriv.Attributes()->IsLong());
		this->Attributes_Mutable()->Price(deriv.Attributes()->Price());
		this->Attributes_Mutable()->SettlementDate(deriv.Attributes()->SettlementDate());
	}
	return *this;
}