#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <memory>
#include "Security.hpp"

class Derivative : public Security
{
public:
	// Constructors/Destructor:
	Derivative(const std::shared_ptr<SecurityAttributes> &attr);
	Derivative(const SecurityAttributes* attr);
	Derivative(const Derivative&);
	virtual ~Derivative();
	// Overloaded Operators:
	Derivative& operator=(const Derivative&);
};


#endif
