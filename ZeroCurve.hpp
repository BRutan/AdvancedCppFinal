#ifndef ZEROCURVE_HPP
#define ZEROCURVE_HPP

#include <unordered_map>

class ZeroCurve
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
