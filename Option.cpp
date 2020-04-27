#include "Option.hpp"

using QQuote = QuantLib::Quote;
using QPricingEngine = QuantLib::PricingEngine;
using QBSMP = QuantLib::BlackScholesMertonProcess;
using QYTS = QuantLib::YieldTermStructure;
using QSimpleQuote = QuantLib::SimpleQuote;
using QFlatForward = QuantLib::FlatForward;
using QBAWEngine = QuantLib::BaroneAdesiWhaleyApproximationEngine;
using QAmericanExercise = QuantLib::AmericanExercise;
using QBlackVolTS = QuantLib::BlackVolTermStructure;
using QBlackConstantVol = QuantLib::BlackConstantVol;

////////////////////
// OptionAttributes definitions:
////////////////////
// Constructors/Destructor:
OptionAttributes::OptionAttributes() : _IsCall(false), DerivativeAttributes(), _Strike(0), _Price(0), _ImpliedVol(0), _TTM(0),
	_DivYield(0), _UnderlyingPrice(0)
{

}
OptionAttributes::OptionAttributes(bool isCall, bool isLong, double premium, double riskFree, double divYield, double underlyingPrice,
	const OptionChainRow& row, const QuantLib::Date &settle, const QuantLib::Date &exp) :
	_IsCall(isCall), _Strike(row.Strike()),  
	_ImpliedVol(row.ImpliedVol()), _TTM(QuantLib::Actual365Fixed().yearFraction(settle, exp)), 
	_DivYield(divYield), _UnderlyingPrice(underlyingPrice), DerivativeAttributes(((isLong) ? row.Ask() : row.Bid()), isLong, settle, exp)
{

}
OptionAttributes::OptionAttributes(const OptionAttributes& attr) : _IsCall(attr._IsCall), _Strike(attr._Strike),
_ImpliedVol(attr._ImpliedVol), _TTM(attr._TTM), _DivYield(attr._DivYield), _UnderlyingPrice(attr._UnderlyingPrice), 
DerivativeAttributes(attr._Price, attr._IsLong, attr._SettlementDate, attr.ExpirationDate())
{

}
OptionAttributes::~OptionAttributes()
{

}
// Accessors:
double OptionAttributes::DividendYield() const
{
	return this->_DivYield;
}
double OptionAttributes::Strike() const
{
	return this->_Strike;
}
double OptionAttributes::Price() const
{
	return this->_Price;
}
double OptionAttributes::ImpliedVol() const
{
	return this->_ImpliedVol;
}
double OptionAttributes::RiskFreeRate() const
{
	return this->_RiskFreeRate;
}
double OptionAttributes::TimeToMaturity() const
{
	return this->_TTM;
}
bool OptionAttributes::IsCall() const
{
	return this->_IsCall;
}
double OptionAttributes::UnderlyingPrice() const
{
	return this->_UnderlyingPrice;
}
// Mutators:
void OptionAttributes::DividendYield(double yield)
{
	this->_DivYield = yield;
}
void OptionAttributes::Strike(double strike)
{
	this->_Strike = strike;
}
void OptionAttributes::Price(double price)
{
	this->_Price = price;
}
void OptionAttributes::ImpliedVol(double iv)
{
	this->_ImpliedVol = iv;
}
void OptionAttributes::RiskFreeRate(double rf)
{
	this->_RiskFreeRate = rf;
}
void OptionAttributes::TimeToMaturity(double ttm)
{
	this->_TTM = ttm;
}
void OptionAttributes::IsCall(bool isCall)
{
	this->_IsCall = isCall;
}
void OptionAttributes::UnderlyingPrice(double price)
{
	this->_UnderlyingPrice = price;
}
// Overloaded Operators:
OptionAttributes& OptionAttributes::operator=(const OptionAttributes &attr)
{
	if (this != &attr)
	{
		this->_DivYield = attr._DivYield;
		this->_ImpliedVol = attr._ImpliedVol;
		this->_IsCall = attr._IsCall;
		this->_Long = attr._Long;
		this->_Price = attr._Price;
		this->_Strike = attr._Strike;
		this->_TTM = attr._TTM;
		this->_UnderlyingPrice = attr._UnderlyingPrice;
	}
	return *this;
}
////////////////////
// Option definitions:
////////////////////
// Constructors/Destructor:
Option::Option() : Derivative(), _OptionObj(nullptr)
{

}
Option::Option(const OptionAttributes& attr) : Derivative(std::make_shared<OptionAttributes>(attr)), 
	_OptionObj(&Option::GenerateOptionObj(attr))
{
	
}
Option::~Option()
{

}
// Accessors:
double Option::Price() const
{
	return dynamic_cast<OptionAttributes*>(this->Attributes().get())->Price();
}
// Mutators:
void Option::SetAttributes(const std::shared_ptr<OptionAttributes>& attr)
{
	this->_Attributes = attr;
}
// Interface Functions:
double Option::ImpliedVolatility(const OptionAttributes &attr, double tol_approx, double tol_consec)
{
	return 0;
}
double Option::Delta() const
{
	return this->_OptionObj->delta();
}
double Option::Gamma() const
{
	return this->_OptionObj->gamma();
}
double Option::Rho() const
{
	return this->_OptionObj->rho();
}
double Option::Theta() const
{
	return this->_OptionObj->theta();
}
double Option::Vega() const
{
	return this->_OptionObj->vega();
}
// Static Methods:
double Option::Delta(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs).delta();
}
double Option::Gamma(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs).gamma();
}
double Option::Rho(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs).rho();
}
double Option::Theta(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs).theta();
}
double Option::Vega(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs).vega();
}
QuantLib::VanillaOption Option::GenerateOptionObj(const OptionAttributes &attr)
{
	auto dayCount = QuantLib::Actual365Fixed();
	auto type = (attr.IsCall()) ? QuantLib::Option::Call : QuantLib::Option::Put;
	auto calendar = QuantLib::UnitedStates();
	auto payoff = boost::shared_ptr<QuantLib::PlainVanillaPayoff>(new QuantLib::PlainVanillaPayoff(type, attr.Strike()));
	auto exercise = boost::shared_ptr<QAmericanExercise>(new QAmericanExercise(attr.SettlementDate(), attr.ExpirationDate()));

	QuantLib::Handle<QQuote> underlying(boost::shared_ptr<QQuote>(new QSimpleQuote(attr.UnderlyingPrice())));
	QuantLib::Handle<QYTS> divTermStruct(boost::shared_ptr<QYTS>(new QFlatForward(attr.SettlementDate(),attr.DividendYield(),dayCount)));
	QuantLib::Handle<QYTS> rfTermStruct(boost::shared_ptr<QYTS>(new QFlatForward(attr.SettlementDate(), attr.RiskFreeRate(), dayCount)));
	QuantLib::Handle<QBlackVolTS> volTermStruct(boost::shared_ptr<QBlackVolTS>(new QBlackConstantVol(attr.SettlementDate(),
		calendar,attr.ImpliedVol(),dayCount)));
	
	auto stochProcess = boost::shared_ptr<QBSMP>(new QBSMP(underlying,divTermStruct,rfTermStruct,volTermStruct));
	auto engine = boost::shared_ptr<QPricingEngine>(new QBAWEngine(stochProcess));
	QuantLib::VanillaOption option(payoff, exercise);
	option.setPricingEngine(engine);

	return option;
}
// Overloaded Operators:
Option& Option::operator=(const Option &opt) 
{
	if (this != &opt)
	{
		this->_Attributes = opt._Attributes;
	}
	return *this;
}