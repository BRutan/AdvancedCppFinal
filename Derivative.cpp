#include "Derivative.hpp"

// Constructors/Destructor:
Derivative::Derivative(const SecurityAttributes* attr) : Security(attr)
{

}
Derivative::Derivative(const std::shared_ptr<SecurityAttributes> &attr) : Security(attr)
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

	}
	return *this;
}