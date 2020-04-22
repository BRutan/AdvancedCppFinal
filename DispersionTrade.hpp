#ifndef DISPERSIONTRADE_HPP
#define DISPERSIONTRADE_HPP

#include <string>
#include <tuple>
#include <unordered_map>
#include "Option.hpp"
#include "Trade.hpp"

class DispersionTrade : public Trade
{
private:
	Option _Index;
	std::unordered_map<std::string, Option> _Constituents;
public:
	// Constructors/Destructor:
	DispersionTrade();
	DispersionTrade(const DispersionTrade&);
	virtual ~DispersionTrade();
	// Accessors:

	// Mutators:

	// Interface Methods:
	static std::pair<double, double> OptimalValueDate();
	
	DispersionTrade& operator=(const DispersionTrade&);
};


#endif