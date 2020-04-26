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
	virtual ~DerivativeAttributes();
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
	// Overloaded Operators:
	Derivative& operator=(const Derivative&);
};

#endif