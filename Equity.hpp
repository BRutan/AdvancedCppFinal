#ifndef EQUITY_HPP
#define EQUITY_HPP

#include "Security.hpp"

class EquityAttributes : SecurityAttributes
{
private:
	double _Price, _MarginRate;
public:
	// Constructors/Destructor:
	EquityAttributes(bool isLong, double price, double margin_rate = 0);
	// Overloaded Operators:
	EquityAttributes& operator=(const EquityAttributes&);
};

class Equity : public Security
{
public:
	// Constructors/Destructor:
	Equity(const EquityAttributes&);
	Equity(const Equity&);
	virtual ~Equity();


	// Overloaded Operator:
	Equity& operator=(const Equity&);
};

#endif