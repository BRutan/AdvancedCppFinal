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

class DispersionTradeAttributes : SecurityAttributes
{
private:
	double _IndexPrice;
	std::unordered_map<std::string, double> _ConstitutentPrices;
public:
	// Constructors/Destructor:
	DispersionTradeAttributes(bool IsLong);
	virtual ~DispersionTradeAttributes();
	// Overloaded Operators:
	DispersionTradeAttributes& operator=(const DispersionTradeAttributes&);
};

class DispersionTrade : public Trade
{
private:
	std::string _IndexName;
	Option _IndexOption;
	std::unordered_map<std::string, std::pair<Option, double>> _ConstituentOptions;
public:
	// Constructors/Destructor:
	DispersionTrade(const std::string&, const Option&, const std::unordered_map<std::string, std::pair<Option, double>>&);
	DispersionTrade(double dateSerial, const std::string &valueDateFolder);
	DispersionTrade(const DispersionTrade&);
	virtual ~DispersionTrade();
	// Accessors:
	const std::string& IndexName() const;
	const Option& IndexOption() const;
	const std::unordered_map<std::string, Option>& ConstitutentOptions() const;
	// Interface Methods:
	static std::pair<DispersionTrade, double> OptimalDispersionTrade(const std::string &optionChainsPaths);
	double ImpliedCorrelation() const;
	double CalculatePNL(const SecurityAttributes*);
	static double ImpliedCorrelation(const std::string &indexName, const OptionChains &chains);
	DispersionTrade& operator=(const DispersionTrade&);
};

#endif