#ifndef OPTION_HPP
#define OPTION_HPP

#include <cmath>
#include <memory>
#include <string>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/juquadraticengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/fdshoutengine.hpp>
#include <ql/time/date.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/utilities/dataformatters.hpp>
#include "OptionChainRow.hpp"
#include "Derivative.hpp"
#include "Security.hpp"

class OptionAttributes : public DerivativeAttributes
{
private:
	double _Strike, _Price, _ImpliedVol, _TTM, _DivYield;
	double _UnderlyingPrice, _RiskFreeRate;
	bool _Long, _IsCall;
public:
	// Constructors/Destructor:
	OptionAttributes();
	OptionAttributes(bool isCall, bool isLong, double premium, double riskFree, double divYield, double underlyingPrice,
		const OptionChainRow& row, const QuantLib::Date &settle, const QuantLib::Date &exp);
	virtual ~OptionAttributes();
	// Accessors:
	double DividendYield() const;
	double ImpliedVol() const;
	bool IsCall() const;
	double Price() const;
	double RiskFreeRate() const;
	double Strike() const;
	double TimeToMaturity() const;
	double UnderlyingPrice() const;
	// Mutators:
	void DividendYield(double);
	void ImpliedVol(double);
	void IsCall(bool);
	void Price(double);
	void RiskFreeRate(double);
	void Strike(double);
	void TimeToMaturity(double);
	void UnderlyingPrice(double);
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
	Option(const OptionAttributes& attr);
	virtual ~Option();
	// Accessors:
	virtual double Price() const;
	// Mutators:
	void SetAttributes(const std::shared_ptr<OptionAttributes>& attr);
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
	static QuantLib::VanillaOption GenerateOptionObj(const OptionAttributes&);
	// Overloaded Operators:
	Option& operator=(const Option&);
};

#endif