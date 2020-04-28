#ifndef OPTION_HPP
#define OPTION_HPP

#include <cmath>
#include <memory>
#include <string>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/juquadraticengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/fdshoutengine.hpp>
#include <ql/time/date.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/utilities/dataformatters.hpp>
#include "Equity.hpp"
#include "OptionChainRow.hpp"
#include "Derivative.hpp"
#include "Security.hpp"

class OptionAttributes : public DerivativeAttributes
{
protected:
	double _Strike, _ImpliedVol;
	double _RiskFreeRate;
	bool _Long, _IsCall;
	EquityAttributes _Underlying;
public:
	// Constructors/Destructor:
	OptionAttributes();
	OptionAttributes(bool isCall, bool isLong, double premium, double riskFree, const OptionChainRow& row, 
		const QuantLib::Date &settle, const QuantLib::Date &exp, const EquityAttributes&);
	OptionAttributes(const OptionAttributes&);
	virtual ~OptionAttributes();
	// Accessors:
	double ImpliedVol() const;
	bool IsCall() const;
	double Price() const;
	double RiskFreeRate() const;
	double Strike() const;
	const EquityAttributes& Underlying() const;
	// Mutators:
	void ImpliedVol(double);
	void IsCall(bool);
	void Price(double);
	void RiskFreeRate(double);
	void Strike(double);
	void Underlying(const EquityAttributes&);
	// Overloaded Operators:
	OptionAttributes& operator=(const OptionAttributes&);
};

class Option : public Derivative
{
private:
	std::shared_ptr<QuantLib::VanillaOption> _OptionObj;
public:
	// Constructors/Destructor:
	Option();
	Option(const OptionAttributes&);
	virtual ~Option();
	// Accessors:
	virtual double Price() const;
	// Mutators:
	void Generate();
	// Interface Functions:
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double ImpliedVolatility() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	static double ImpliedVolatility(const OptionAttributes& attrs, double tol_approx = .0001, double tol_consec = .0001);
	static double Delta(const OptionAttributes&);
	static double Gamma(const OptionAttributes&);
	static double Theta(const OptionAttributes&);
	static double Vega(const OptionAttributes&);
	static double Rho(const OptionAttributes&);
	static std::shared_ptr<QuantLib::VanillaOption> GenerateOptionObj(const OptionAttributes&);
	// Overloaded Operators:
	Option& operator=(const Option&);
};

#endif