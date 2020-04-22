#ifndef BONDFILEROW_HPP
#define BONDFILEROW_HPP

#include <sstream>
#include <string>
#include "FileRow.hpp"

class BondFileRow : FileRow
{
private:
	double _Tenor, _Yield;
public:
	// Constructors/Destructor:
	BondFileRow(const std::string& row);
	BondFileRow(const BondFileRow&);
	virtual ~BondFileRow();
	// Accessors:
	double Tenor() const;
	double Yield() const;
	// Interface Methods:
	virtual void ParseRow(const std::string& row);
	// Overloaded Operators:
	BondFileRow& operator=(const BondFileRow&);
};

#endif


