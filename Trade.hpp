#ifndef TRADE_HPP
#define TRADE_HPP

#include <memory>
#include <string>
#include "Security.hpp"

enum class TradeType
{
	OPTION,
	DISPERSION_TRADE,
	EQUITY,
	BOND
};

class Trade
{
private:
	std::shared_ptr<Security> _Security;
public:
	// Constructor/Destructor:
	Trade(Security*);
	virtual ~Trade();
	// Interface Methods:
	virtual double CalculatePNL(const SecurityAttributes*) = 0;
	// Overloaded Operators:
	Trade& operator=(const Trade&);
};

#endif