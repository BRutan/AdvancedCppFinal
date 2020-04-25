#ifndef BJERKSUNDSTENSLANDPRICING_HPP
#define BJERKSUNDSTENSLANDPRICING_HPP

#include <cmath>
#include <memory>
#include <string>

class Option;
class OptionAttributes;

#include "Derivative.hpp"

class BjersundStenslandPricing : public Derivative
{
public:
	// Constructors/Destructor:
	BjersundStenslandPricing();
	BjersundStenslandPricing(const Option& opt);
	BjersundStenslandPricing(const OptionAttributes& attr);
	virtual ~BjersundStenslandPricing();
	// Interface Methods:
	virtual double Price() const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Rho() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Price() const;
	// Overloaded Operators:
	BjersundStenslandPricing& operator=(const BjersundStenslandPricing&);
};

#endif
