#ifndef BONDFILEROW_HPP
#define BONDFILEROW_HPP

#include <sstream>
#include <string>
#include "FileRow.hpp"

class BondFileRow : FileRow
{
private:
	std::string _Name;
	double _Tenor, _Yield, _PresentValue, _Coupon;
public:
	// Constructors/Destructor:
	BondFileRow(const std::string& row);
	BondFileRow(const BondFileRow&);
	virtual ~BondFileRow();
	// Accessors:
	double Coupon() const;
	double PresentValue() const;
	double Tenor() const;
	double Yield() const;
	// Interface Methods:
	virtual void ParseRow(const std::string& row);
	// Overloaded Operators:
	BondFileRow& operator=(const BondFileRow&);
	friend std::ostream& operator<<(std::ostream &stream, const BondFileRow &row)
	{
		stream << row._Name << ',' << row._Tenor << ',' << row._Yield << ',';
		stream << row._PresentValue << ',' << row._Coupon;
		return stream;
	}
};

#endif