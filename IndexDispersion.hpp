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
#include "Security.hpp"

class IndexDispersionAttributes : public DerivativeAttributes
{
private:
	std::string _IndexName;
	Option _IndexOption;
	std::unordered_map<std::string, std::pair<Option, double>> _ConstituentOptions;
	void _SetAttributes();
public:
	// Constructors/Destructor:
	IndexDispersionAttributes();
	IndexDispersionAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
		const std::unordered_map<std::string, std::pair<Option, double>> ConstitutentOptions, 
		const QuantLib::Date &settle, const QuantLib::Date &exp);
	IndexDispersionAttributes(const IndexDispersionAttributes&);
	virtual ~IndexDispersionAttributes();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions() const;
	// Mutators:
	void ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>>&);
	void IndexName(const std::string&);
	void IndexOption(const Option&);
	Option& IndexOption_Mutable();
	std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions_Mutable();
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
	static std::pair<IndexDispersion, double> OptimalDispersionTrade(const OptionChainPathGenerator &gen, 
		const IndexDispersionAttributes &attrs, const std::unordered_map<std::string,EquityAttributes>&, double);
	virtual double Price() const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	IndexDispersion& operator=(const IndexDispersion&);
};

#endif