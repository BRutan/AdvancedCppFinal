#ifndef DISPERSIONTRADE_HPP
#define DISPERSIONTRADE_HPP

#include <ql/time/date.hpp>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include "ComponentWeightsFileRow.hpp"
#include "Equity.hpp"
#include "Option.hpp"
#include "OptionChains.hpp"
#include "PNLFileRow.hpp"
#include "Security.hpp"

class IndexDispersionAttributes : public DerivativeAttributes
{
private:
	std::string _IndexName;
	Option _IndexOption;
	std::unordered_map<std::string, std::pair<Option, double>> _ConstituentOptions;
	void _SetAttributes();
	void _InitializeAttributes();
public:
	// Constructors/Destructor:
	IndexDispersionAttributes();
	IndexDispersionAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
		const std::unordered_map<std::string, std::pair<Option, double>> ConstitutentOptions, 
		const QuantLib::Date &settle, const QuantLib::Date &exp);
	IndexDispersionAttributes(const IndexDispersionAttributes&);
	virtual ~IndexDispersionAttributes();
	// Accessors:
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions() const;
	const QuantLib::Date& ExpirationDate() const;
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const QuantLib::Date& SettlementDate() const;
	double RiskfreeRate() const;
	// Mutators:
	void ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>>&);
	void ExpirationDate(const QuantLib::Date&);
	void IndexName(const std::string&);
	void IndexOption(const Option&);
	virtual void IsLong(bool) override;
	void RiskFreeRate(double);
	void SettlementDate(const QuantLib::Date&);
	void Generate();
	Option& IndexOption_Mutable();
	std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions_Mutable();
	// Interface Methods:
	static double ApproxExerciseDelta(double futurePrice, double iv, double tenor, double strike);
	static double TargetStrike(double futurePrice, double iv, double tenor, double x);
	// Overloaded Operators:
	IndexDispersionAttributes& operator=(const IndexDispersionAttributes&);
};

class IndexDispersion : public Derivative
{
public:
	// Constructors/Destructor:
	IndexDispersion();
	IndexDispersion(const IndexDispersionAttributes&);
	IndexDispersion(const IndexDispersion&);
	virtual ~IndexDispersion();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstitutentOptions() const;
	// Interface Methods:
	double ImpliedCorrelation() const;
	static double ImpliedCorrelation(const IndexDispersionAttributes &attr);
	virtual double Price() const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	IndexDispersion& operator=(const IndexDispersion&);
	PNLFileRow operator-(const IndexDispersion&);
};

#endif