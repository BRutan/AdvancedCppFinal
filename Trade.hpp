#ifndef TRADE_HPP
#define TRADE_HPP

#include <memory>
#include <string>
#include "Security.hpp"

class Trade
{
private:
	std::shared_ptr<SecurityAttributes> _Attributes;
public:
	// Constructor/Destructor:
	Trade(const std::shared_ptr<SecurityAttributes> attr);
	virtual ~Trade();
	// Accessors:
	std::shared_ptr<SecurityAttributes> Attributes() const;
	// Interface Methods:
	virtual double CalculatePNL(const std::shared_ptr<SecurityAttributes>&) = 0;
	virtual double Delta() const = 0;
	virtual double Gamma() const = 0;
	virtual double Theta() const = 0;
	virtual double Vega() const = 0;
	// Overloaded Operators:
	Trade& operator=(const Trade&);
};

#endif