#ifndef BOND_HPP
#define BOND_HPP

#include "BondFile.hpp"
#include "Security.hpp"
#include "Trade.hpp"

class BondAttributes : SecurityAttributes
{
private:
	double _Tenor, _Coupon, _Yield, _PresentValue;
public:
	// Constructors/Destructor:
	BondAttributes(const BondFileRow&);
	virtual ~BondAttributes();

	// Overloaded Operators:
	BondAttributes& operator=(const BondAttributes&);
};

class Bond : Security
{
public:
	// Constructors/Destructor:
	Bond();
	virtual ~Bond();
	// Overloaded Operators:
	Bond& operator=(const Bond&);
};


#endif
