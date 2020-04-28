#include "Option.hpp"

using QQuote = QuantLib::Quote;
using QPricingEngine = QuantLib::PricingEngine;
using QGBSMP = QuantLib::GeneralizedBlackScholesProcess;
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
OptionAttributes::OptionAttributes() : _IsCall(false), DerivativeAttributes(), _Strike(0), _ImpliedVol(0),
	_Underlying()
{

}
OptionAttributes::OptionAttributes(bool isCall, bool isLong, double premium, double riskFree,
	const OptionChainRow& row, const QuantLib::Date &settle, const QuantLib::Date &exp, const EquityAttributes&) :
	_IsCall(isCall), _Strike(row.Strike()),  
	_ImpliedVol(row.ImpliedVol()), DerivativeAttributes(((isLong) ? row.Ask() : row.Bid()), isLong, settle, exp)
{

}
OptionAttributes::OptionAttributes(const OptionAttributes& attr) : _IsCall(attr._IsCall), _Strike(attr._Strike),
_ImpliedVol(attr._ImpliedVol), 
	DerivativeAttributes(attr._Price, attr._IsLong, attr._SettlementDate, attr.ExpirationDate()), _Underlying(attr._Underlying)
{

}
OptionAttributes::~OptionAttributes()
{

}
// Accessors:
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
bool OptionAttributes::IsCall() const
{
	return this->_IsCall;
}
const EquityAttributes& OptionAttributes::Underlying() const
{
	return this->_Underlying;
}
// Mutators:
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
void OptionAttributes::IsCall(bool isCall)
{
	this->_IsCall = isCall;
}
void OptionAttributes::Underlying(const EquityAttributes& attr)
{
	this->_Underlying = attr;
}
// Overloaded Operators:
OptionAttributes& OptionAttributes::operator=(const OptionAttributes &attr)
{
	if (this != &attr)
	{
		this->_ImpliedVol = attr._ImpliedVol;
		this->_IsCall = attr._IsCall;
		this->_Long = attr._Long;
		this->_Price = attr._Price;
		this->_Strike = attr._Strike;
		this->_Underlying = attr._Underlying;
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
	_OptionObj(Option::GenerateOptionObj(attr))
{
	
}
Option::~Option()
{

}
// Accessors:
double Option::Price() const
{
	double price;
	if (this->_Attributes->Price() <= 0)
	{
		price = dynamic_cast<OptionAttributes*>(this->Attributes().get())->Price();
	}
	else
	{
		price = this->_Attributes->Price();
	}
	return (price * (this->_Attributes->IsLong()) ? 1 : -1);
}
// Mutators
void Option::Generate()
{
	auto attr = dynamic_cast<OptionAttributes*>(this->_Attributes.get());
	this->_OptionObj = Option::GenerateOptionObj(*attr);
}
// Interface Functions:
double Option::ImpliedVolatility() const
{
	if (std::dynamic_pointer_cast<OptionAttributes>(this->_Attributes)->ImpliedVol() <= 0)
	{
		//return this->_OptionObj->impliedVolatility();
	}
	return std::dynamic_pointer_cast<OptionAttributes>(this->_Attributes)->ImpliedVol();
}
double Option::ImpliedVolatility(const OptionAttributes &attr, double tol_approx, double tol_consec)
{
	return 0;
}
double Option::Delta() const
{
	return this->_OptionObj->delta() * ((this->_Attributes->IsLong()) ? 1 : -1);
}
double Option::Gamma() const
{
	return this->_OptionObj->gamma();
}
double Option::Rho() const
{
	return this->_OptionObj->rho() * ((this->_Attributes->IsLong()) ? 1 : -1);
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
	return Option::GenerateOptionObj(attrs)->delta();
}
double Option::Gamma(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs)->gamma();
}
double Option::Rho(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs)->rho();
}
double Option::Theta(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs)->theta();
}
double Option::Vega(const OptionAttributes& attrs)
{
	return Option::GenerateOptionObj(attrs)->vega();
}
std::shared_ptr<QuantLib::VanillaOption> Option::GenerateOptionObj(const OptionAttributes &opAttr)
{
	auto eqAttr = opAttr.Underlying();
	auto dayCount = QuantLib::Actual365Fixed();
	auto type = (opAttr.IsCall()) ? QuantLib::Option::Call : QuantLib::Option::Put;
	auto calendar = QuantLib::UnitedStates();
	auto payoff = boost::shared_ptr<QuantLib::PlainVanillaPayoff>(new QuantLib::PlainVanillaPayoff(type, opAttr.Strike()));
	auto exercise = boost::shared_ptr<QAmericanExercise>(new QAmericanExercise(opAttr.SettlementDate(), opAttr.ExpirationDate()));

	QuantLib::Handle<QQuote> underlying(boost::shared_ptr<QQuote>(new QSimpleQuote(eqAttr.Price())));
	QuantLib::Handle<QYTS> divTermStruct(boost::shared_ptr<QYTS>(new QFlatForward(opAttr.SettlementDate(),eqAttr.DividendYield(),dayCount)));
	QuantLib::Handle<QYTS> rfTermStruct(boost::shared_ptr<QYTS>(new QFlatForward(opAttr.SettlementDate(),opAttr.RiskFreeRate(), dayCount)));
	QuantLib::Handle<QBlackVolTS> volTermStruct(boost::shared_ptr<QBlackVolTS>(new QBlackConstantVol(opAttr.SettlementDate(),
		calendar,opAttr.ImpliedVol(),dayCount)));
	
	auto stochProcess = boost::shared_ptr<QBSMP>(new QBSMP(underlying,divTermStruct,rfTermStruct,volTermStruct));
	auto engine = boost::shared_ptr<QPricingEngine>(new QBAWEngine(stochProcess));
	auto option = std::make_shared< QuantLib::VanillaOption>(QuantLib::VanillaOption(payoff, exercise));
	option->setPricingEngine(engine);
	return option;
}
// Overloaded Operators:
Option& Option::operator=(const Option &opt) 
{
	if (this != &opt)
	{
		this->_OptionObj = opt._OptionObj;
		this->_Attributes = opt._Attributes;
	}
	return *this;
}