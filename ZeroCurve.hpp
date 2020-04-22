#ifndef ZEROCURVE_HPP
#define ZEROCURVE_HPP

#include <unordered_map>
#include "Security.hpp"

class ZeroCurve : Security
{
private:
	std::unordered_map<double, double> _DiscountFactors, _ZeroRates;
public:
	// Constructors/Destructor:
	ZeroCurve();
	virtual ~ZeroCurve();
	// 


	ZeroCurve& operator=(const ZeroCurve&);
};



#endif
