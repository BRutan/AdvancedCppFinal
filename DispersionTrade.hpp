#ifndef DISPERSIONTRADE_HPP
#define DISPERSIONTRADE_HPP

#include <ql/time/date.hpp>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include "ComponentWeightsFileRow.hpp"
#include "Option.hpp"
#include "OptionChains.hpp"
#include "Trade.hpp"
#include "Security.hpp"

class DispersionTradeAttributes : public DerivativeAttributes
{
private:
	std::string _IndexName;
	Option _IndexOption;
	std::unordered_map<std::string, std::pair<Option, double>> _ConstituentOptions;
	void _SetAttributesCorrectly();
public:
	// Constructors/Destructor:
	DispersionTradeAttributes();
	DispersionTradeAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
		const std::unordered_map<std::string, std::pair<Option, double>> ConstitutentOptions, 
		const QuantLib::Date &settle, const QuantLib::Date &exp);
	DispersionTradeAttributes(const DispersionTradeAttributes&);
	virtual ~DispersionTradeAttributes();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions() const;
	// Mutators:
	void ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>>&);
	void IndexName(const std::string&);
	void IndexOption(const Option&);
	// Overloaded Operators:
	DispersionTradeAttributes& operator=(const DispersionTradeAttributes&);
};

class DispersionTrade : public Trade
{
public:
	// Constructors/Destructor:
	DispersionTrade(const DispersionTradeAttributes&);
	DispersionTrade(const DispersionTrade&);
	virtual ~DispersionTrade();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstitutentOptions() const;
	// Interface Methods:
	double ImpliedCorrelation() const;
	static double ImpliedCorrelation(const DispersionTradeAttributes &attr);
	static std::pair<DispersionTrade, double> OptimalDispersionTrade(const OptionChainPathGenerator &gen, const DispersionTradeAttributes &attrs);
	virtual double CalculatePNL(const std::shared_ptr<SecurityAttributes>&);
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	DispersionTrade& operator=(const DispersionTrade&);
};

#endif