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
	BondAttributes(const BondFileRow&);

};

class Bond : Security
{

};


#endif
