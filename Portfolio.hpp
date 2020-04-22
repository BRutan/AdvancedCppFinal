#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <unordered_map>
#include "Trade.hpp"

class Portfolio : Trade
{
private:
	std::unordered_map<std::string, Trade*> _Trades;
public:
	// Constructors/Destructor:
	Portfolio();
	Portfolio(const Portfolio&);


	// Overloaded Operators:
	Portfolio& operator=(const Portfolio&);
};



#endif
