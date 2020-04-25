#ifndef OPTION_HPP
#define OPTION_HPP

#include "OptionChainRow.hpp"
#include "Derivative.hpp"
#include "Security.hpp"

class OptionAttributes : public SecurityAttributes
{
private:
	double _Strike, _Price, _ImpliedVol, _TTM, _DivYield;
	bool _Long, _IsCall;
public:
	// Constructors/Destructor:
	OptionAttributes();
	OptionAttributes(bool isCall, bool isLong, double tenor, double divYield, const OptionChainRow& row);
	virtual ~OptionAttributes();
	// Accessors:
	double DividendYield() const;
	double ImpliedVol() const;
	bool IsCall() const;
	double Price() const;
	double Strike() const;
	double TimeToMaturity() const;
	// Mutators:
	void DividendYield(double);
	void ImpliedVol(double);
	void IsCall(bool);
	void Price(double);
	void Strike(double);
	void TimeToMaturity(double);
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
	virtual double Price(const std::shared_ptr<SecurityAttributes>&) const;
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
