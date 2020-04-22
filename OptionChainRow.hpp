#ifndef OPTIONCHAINROW_HPP
#define OPTIONCHAINROW_HPP

#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>
#include "FileRow.hpp"

class OptionChainRow : public FileRow
{
private:
	double _Strike, _LastPrice, _Bid, _Ask, _Change, _PercentChange, _Volume,
		_OpenInterest, _ImpliedVol;
	void _ParseCell(const std::string &cell, const std::size_t &index);
public:
	// Constructors/Destructor:
	OptionChainRow(const std::string& row);
	OptionChainRow(const OptionChainRow&);
	virtual ~OptionChainRow();
	// Accessors:
	double Strike() const;
	double LastPrice() const;
	double Bid() const;
	double Ask() const;
	double Change() const;
	double PercentChange() const;
	double Volume() const;
	double OpenInterest() const;
	double ImpliedVol() const;
	// Mutators:
	virtual void ParseRow(const std::string& row);
	// Overloaded Operators:
	OptionChainRow& operator=(const OptionChainRow&);
	void operator<<(const std::string &row);
	friend std::ostream& operator<<(std::ostream& stream, const OptionChainRow &row)
	{
		stream << row._Strike << ',' << row._LastPrice << ',' << row._Bid << ',';
		stream << row._Ask << ',' << row._Change << ',' << row._PercentChange << ',';
		stream << row._Volume << ',' << row._OpenInterest << ',' << row._ImpliedVol;
		return stream;
	}
};

#endif