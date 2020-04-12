#ifndef OPTIONCHAINROW_HPP
#define OPTIONCHAINROW_HPP

#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>

class OptionChainRow
{
private:
	float _Strike, _LastPrice, _Bid, _Ask, _Change, _PercentChange, _Volume,
		_OpenInterest, _ImpliedVol;
	void _ParseCell(const std::string &cell, const std::size_t &index);
public:
	// Constructors/Destructor:
	OptionChainRow(const std::string& row);
	virtual ~OptionChainRow();
	// Accessors:
	float Strike() const;
	float LastPrice() const;
	float Bid() const;
	float Ask() const;
	float Change() const;
	float PercentChange() const;
	float Volume() const;
	float OpenInterest() const;
	float ImpliedVol() const;
	// Mutators:
	void ParseRow(const std::string& row);
	// Overloaded Operators:
	void operator<<(const std::string &row);
	friend std::ostream& operator<<(std::ostream& stream, const OptionChainRow &row)
	{
		stream << row._Strike << "," << row._LastPrice << "," << row._Bid << ",";
		stream << row._Ask << "," << row._Change << "," << row._PercentChange << ",";
		stream << row._Volume << "," << row._OpenInterest << "," << row._ImpliedVol;
		return stream;
	}
};

#endif