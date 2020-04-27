#ifndef BOND_HPP
#define BOND_HPP

#include <ql/time/date.hpp>
#include "BondFile.hpp"
#include "Security.hpp"

class BondAttributes : SecurityAttributes
{
private:
	double _Tenor, _Coupon, _Yield, _PresentValue;
public:
	// Constructors/Destructor:
	BondAttributes();
	BondAttributes(const QuantLib::Date &dt, const BondFileRow&);
	virtual ~BondAttributes();
	// Overloaded Operators:
	BondAttributes& operator=(const BondAttributes&);
};

class Bond : Security
{
private:
	QuantLib::Date _MaturityDate;
public:
	// Constructors/Destructor:
	Bond(Bond& bd);
	Bond(BondAttributes& attr);
	Bond(const QuantLib::Date&);
	virtual ~Bond();
	// Overloaded Operators:
	Bond& operator=(const Bond&);
};


#endif
