#include "Derivative.hpp"

/////////////////////////
// DerivativeAttributes Definitions
/////////////////////////
DerivativeAttributes::DerivativeAttributes() : SecurityAttributes(), _ExpirationDate()
{

}
DerivativeAttributes::DerivativeAttributes(bool isLong, const QuantLib::Date& settle, const QuantLib::Date& exp) : 
	SecurityAttributes(settle, isLong), _ExpirationDate(exp)
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
Derivative::Derivative(const std::shared_ptr<SecurityAttributes>& attr) : Security(attr)
{

}
Derivative::Derivative(const Derivative& deriv) : Security(deriv._Attributes)
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
		this->_Attributes = deriv._Attributes;
	}
	return *this;
}