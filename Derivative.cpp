#include "Derivative.hpp"

/////////////////////////
// DerivativeAttributes Definitions
/////////////////////////
DerivativeAttributes::DerivativeAttributes() : SecurityAttributes(), _ExpirationDate()
{

}
DerivativeAttributes::DerivativeAttributes(double price, bool isLong, const QuantLib::Date& settle, const QuantLib::Date& exp) : 
	_ExpirationDate(exp), SecurityAttributes(price, settle, isLong)
{
	
}
DerivativeAttributes::DerivativeAttributes(DerivativeAttributes &attr) : _ExpirationDate(attr._ExpirationDate), 
	SecurityAttributes(attr)
{

}
DerivativeAttributes::DerivativeAttributes(DerivativeAttributes && attr) : _ExpirationDate(std::move(attr._ExpirationDate)),
	SecurityAttributes(std::move(attr))
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
Derivative::Derivative(DerivativeAttributes& attr) : Security(static_cast<SecurityAttributes&>(attr))
{

}
Derivative::Derivative(Derivative& deriv) : Security(deriv._Attributes)
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