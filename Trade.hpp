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
	std::shared_ptr<SecurityAttributes> _Attributes;
public:
	// Constructor/Destructor:
	Trade(const std::shared_ptr<SecurityAttributes> attr);
	Trade(const SecurityAttributes*);
	virtual ~Trade();
	// Accessors:
	std::shared_ptr<SecurityAttributes> Attributes() const;
	// Interface Methods:
	virtual double CalculatePNL(const SecurityAttributes*) = 0;
	// Overloaded Operators:
	Trade& operator=(const Trade&);
};

#endif