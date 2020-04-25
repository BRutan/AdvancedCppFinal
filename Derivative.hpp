#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <ql/time/date.hpp>
#include <memory>
#include "Security.hpp"

class DerivativeAttributes : public SecurityAttributes
{
private:
	QuantLib::Date _ExpirationDate;
public:
	// Constructors/Destructor:
	DerivativeAttributes();
	DerivativeAttributes(bool isLong, const QuantLib::Date& settle, const QuantLib::Date& exp);
	virtual ~DerivativeAttributes() = 0;
	// Accessors:
	const QuantLib::Date& ExpirationDate() const;
	// Mutators:
	void ExpirationDate(const QuantLib::Date& dt);
	// Overloaded Operators:
	DerivativeAttributes& operator=(const DerivativeAttributes&);
};

class Derivative : public Security
{
public:
	// Constructors/Destructor:
	Derivative();
	Derivative(const std::shared_ptr<SecurityAttributes> &attr);
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
