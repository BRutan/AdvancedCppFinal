#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <unordered_map>
#include "Derivative.hpp"
#include "Trade.hpp"

class Portfolio : Derivative
{
private:
	std::unordered_map<std::string, Security*> _Securities;
public:
	// Constructors/Destructor:
	Portfolio();
	Portfolio(const Portfolio&);
	// Accessors:

	// Interface Methods:
	virtual double Price() const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	// Overloaded Operators:
	Portfolio& operator=(const Portfolio&);
};



#endif
