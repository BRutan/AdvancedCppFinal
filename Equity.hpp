#ifndef EQUITY_HPP
#define EQUITY_HPP

#include "ComponentWeightsFileRow.hpp"
#include "Security.hpp"

class EquityAttributes : public SecurityAttributes
{
private:
	double _MarginRate, _DividendYield;
public:
	// Constructors/Destructor:
	EquityAttributes();
	EquityAttributes(double price, const QuantLib::Date &settle, bool isLong, double margin_rate, double dividendYield);
	explicit EquityAttributes(const EquityAttributes&);
	// Accessors:
	double MarginRate() const;
	double DividendYield() const;
	// Mutators:
	void MarginRate(double);
	void DividendYield(double);
	// Overloaded Operators:
	EquityAttributes& operator=(const EquityAttributes&);
};

class Equity : public Security
{
public:
	// Constructors/Destructor:
	Equity();
	Equity(const EquityAttributes&);
	Equity(const Equity&);
	virtual ~Equity();
	// Accessors:
	const EquityAttributes& GetAttributes() const;
	// Mutators:
	void SetAttributes(const EquityAttributes&);
	// Interface Methods:
	// Interface Methods:
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	// Overloaded Operator:
	Equity& operator=(const Equity&);
};

#endif