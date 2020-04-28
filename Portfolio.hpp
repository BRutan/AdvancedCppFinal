#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <unordered_map>
#include "Derivative.hpp"
#include "PNLFileRow.hpp"

class Portfolio : Derivative
{
private:
	std::unordered_map<std::string, std::shared_ptr<Security>> _Securities;
public:
	// Constructors/Destructor:
	Portfolio();
	Portfolio(const Portfolio&);
	// Accessors:
	const std::unordered_map<std::string, std::shared_ptr<Security>>& Securities() const;
	// Interface Methods:
	virtual double Price() const;
	double CalculatePNL(const Portfolio&) const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	Portfolio CreateCopy() const;
	// Overloaded Operators:
	Portfolio& operator=(const Portfolio&);
	PNLFileRow operator-(const Portfolio&);
};


#endif
