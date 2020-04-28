#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <ql/time/date.hpp>
#include <ql/time/daycounters/all.hpp>
#include <memory>
#include "Security.hpp"

class DerivativeAttributes : public SecurityAttributes
{
protected:
	QuantLib::Date _ExpirationDate;
public:
	// Constructors/Destructor:
	DerivativeAttributes();
	DerivativeAttributes(double price, bool isLong, const QuantLib::Date& settle, const QuantLib::Date& exp);
	virtual ~DerivativeAttributes();
	// Accessors:
	const QuantLib::Date& ExpirationDate() const;
	// Mutators:
	void ExpirationDate(const QuantLib::Date& dt);
	// Interface Methods:
	double TimeToMaturity() const;
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
	// Overloaded Operators:
	Derivative& operator=(const Derivative&);
};

#endif