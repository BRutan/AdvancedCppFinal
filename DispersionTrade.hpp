#ifndef DISPERSIONTRADE_HPP
#define DISPERSIONTRADE_HPP

#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include "Option.hpp"
#include "OptionChains.hpp"
#include "Trade.hpp"
#include "Security.hpp"

class DispersionTradeAttributes : public SecurityAttributes
{
private:
	std::string _IndexName;
	Option _IndexOption;
	std::unordered_map<std::string, std::pair<Option, double>> _ConstituentOptions;
public:
	// Constructors/Destructor:
	DispersionTradeAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
		const std::unordered_map<std::string, std::pair<Option, double>> ConstitutentOptions);
	DispersionTradeAttributes(const DispersionTradeAttributes&);
	virtual ~DispersionTradeAttributes();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, std::pair<Option, double>>& ConstituentOptions() const;
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
	static std::pair<DispersionTrade, double> OptimalDispersionTrade(const std::string &valueDateFolder, unsigned expMonth,
			unsigned expDay, unsigned expYear, const DispersionTradeAttributes &attrs);
	double CalculatePNL(const SecurityAttributes*);
	virtual double Delta() const;
	static double ImpliedCorrelation(const std::string &indexName, const OptionChains &chains);
	DispersionTrade& operator=(const DispersionTrade&);
};

#endif