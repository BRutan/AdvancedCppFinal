#ifndef TRADEFACTORY_HPP
#define TRADEFACTORY_HPP

#include <string>
#include "Trade.hpp"

class TradeFactory
{
private:

public:
	// Constructors/Destructor:
	TradeFactory();
	virtual ~TradeFactory();

	Trade* CreateTrade(
	TradeFactory& operator=(const TradeFactory&);
};


#endif
