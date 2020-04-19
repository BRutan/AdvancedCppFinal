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
	float _Strike, _LastPrice, _Bid, _Ask, _Change, _PercentChange, _Volume,
		_OpenInterest, _ImpliedVol;
public:
	/////////////////////////////
	// Constructors/Destructor:
	/////////////////////////////
	OptionChainRow(const std::string& row)
	{
		this->ParseRow(row);
	}
	virtual ~OptionChainRow()
	{

	}
	/////////////////////////////
	// Accessors:
	/////////////////////////////
	float Strike() const
	{
		return this->_Strike;
	}
	float LastPrice() const
	{
		return this->_LastPrice;
	}
	float Bid() const
	{
		return this->_Bid;
	}
	float Ask() const
	{
		return this->_Ask;
	}
	float Change() const
	{
		return this->_Change;
	}
	float PercentChange() const
	{
		return this->_PercentChange;
	}
	float Volume() const
	{
		return this->_Volume;
	}
	float OpenInterest() const
	{
		return this->_OpenInterest;
	}
	float ImpliedVol() const
	{
		return this->_ImpliedVol;
	}
	/////////////////////////////
	// Mutators:
	/////////////////////////////
	virtual void ParseRow(const std::string& row)
	{
		std::istringstream line(row), parser;
		std::string cell;
		std::size_t index = 0;
		while (std::getline(line, cell, ',') && index < 12)
		{
			if (index > 1)
				this->_ParseCell(cell, index);
			++index;
		}
	}
	/////////////////////////////
	// Overloaded Operators:
	/////////////////////////////
	void operator<<(const std::string &row)
	{
		this->ParseRow(row);
	}
	friend std::ostream& operator<<(std::ostream& stream, const OptionChainRow &row)
	{
		stream << row._Strike << ',' << row._LastPrice << ',' << row._Bid << ',';
		stream << row._Ask << ',' << row._Change << ',' << row._PercentChange << ',';
		stream << row._Volume << ',' << row._OpenInterest << ',' << row._ImpliedVol;
		return stream;
	}
private:
	void _ParseCell(const std::string &cell, const std::size_t &index)
	{
		float val;
		std::istringstream stream(cell);
		switch (index)
		{
		case 3:
			this->_Strike = (stream >> val) ? val : 0;
			break;
		case 4:
			this->_LastPrice = (stream >> val) ? val : 0;
			break;
		case 5:
			this->_Bid = (stream >> val) ? val : 0;
			break;
		case 6:
			this->_Ask = (stream >> val) ? val : 0;
			break;
		case 7:
			this->_Change = (stream >> val) ? val : 0;
			break;
		case 8:
			this->_PercentChange = (stream >> val) ? val : 0;
			break;
		case 9:
			this->_Volume = (stream >> val) ? val : 0;
			break;
		case 10:
			this->_OpenInterest = (stream >> val) ? val : 0;
			break;
		case 11:
			this->_ImpliedVol = (stream >> val) ? val : 0;
			break;
		}
	}
};

#endif