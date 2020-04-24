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
	OptionAttributes();
	OptionAttributes(bool isCall, bool isLong, double tenor, const OptionChainRow& row);
	virtual ~OptionAttributes();
	// Accessors:
	double Price() const;
	double Strike() const;
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
	Option();
	Option(const OptionAttributes& attr);
	virtual ~Option();
	// Accessors:
	virtual double Price() const;
	virtual double Price(const SecurityAttributes*) const;
	// Interface Functions:
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	static double ImpliedVolatility(const OptionAttributes& attrs, double tol_approx = .0001, double tol_consec = .0001);
	static double Delta(const OptionAttributes&);
	static double Gamma(const OptionAttributes&);
	static double Theta(const OptionAttributes&);
	static double Vega(const OptionAttributes&);
	static double Rho(const OptionAttributes&);
	// Overloaded Operators:
	Option& operator=(const Option&);
};


#endif
