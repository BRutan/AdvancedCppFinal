#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <memory>
#include "Security.hpp"

class Derivative : public Security
{
public:
	// Constructors/Destructor:
	Derivative();
	Derivative(const std::shared_ptr<SecurityAttributes> &attr);
	Derivative(const SecurityAttributes* attr);
	Derivative(const Derivative&);
	virtual ~Derivative();
	// Interface Methods:
	virtual double Delta() const = 0;
	virtual double Gamma() const = 0;
	virtual double Theta() const = 0;
	virtual double Vega() const = 0;
	virtual double Rho() const = 0;
	// Overloaded Operators:
	Derivative& operator=(const Derivative&);
};


#endif
