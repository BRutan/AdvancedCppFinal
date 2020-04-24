#ifndef OPTION_HPP
#define OPTION_HPP

#include "OptionChainRow.hpp"
#include "Derivative.hpp"
#include "Security.hpp"

class OptionAttributes : public SecurityAttributes
{
private:
	double _Strike, _Price, _ImpliedVol, _TTM;
	bool _Long, _IsCall;
public:
	// Constructors/Destructor:
	OptionAttributes(bool isCall, bool isLong, double tenor, const OptionChainRow& row);
	virtual ~OptionAttributes();
	// Accessors:
	double Strike() const;
	double Price() const;
	double ImpliedVol() const;
	double TimeToMaturity() const;
	bool IsCall() const;
	// Mutators:
	void Strike(double);
	void Price(double);
	void ImpliedVol(double);
	void TimeToMaturity(double);
	void IsCall(bool);
	// Overloaded Operators:
	OptionAttributes& operator=(const OptionAttributes&);
};

class Option : public Derivative
{
public:
	// Constructors/Destructor:
	Option(const OptionAttributes& attr);
	virtual ~Option();
	// Accessors:
	virtual double Price() const;
	virtual double Price(const SecurityAttributes*) const;
	// Interface Functions:
	static double BlackScholesValuation(const OptionAttributes&);
	static double ImpliedVolatility(const OptionAttributes&);
	// Overloaded Operators:
	Option& operator=(const Option&);
};


#endif
