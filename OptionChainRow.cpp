#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include "OptionChainRow.hpp"

// Constructors/Destructor:
OptionChainRow::OptionChainRow(const std::string& row)
{
	this->ParseRow(row);
}
OptionChainRow::OptionChainRow(const OptionChainRow &row) : _Ask(row._Ask), _Bid(row._Bid), _Change(row._Change), _PercentChange(row._PercentChange),
	_Volume(row._Volume), _OpenInterest(row._OpenInterest), _ImpliedVol(row._ImpliedVol)
{

}
OptionChainRow::~OptionChainRow()
{

}
// Accessors:
double OptionChainRow::Strike() const
{
	return this->_Strike;
}
double OptionChainRow::LastPrice() const
{
	return this->_LastPrice;
}
double OptionChainRow::Bid() const
{
	return this->_Bid;
}
double OptionChainRow::Ask() const
{
	return this->_Ask;
}
double OptionChainRow::Change() const
{
	return this->_Change;
}
double OptionChainRow::PercentChange() const
{
	return this->_PercentChange;
}
double OptionChainRow::Volume() const
{
	return this->_Volume;
}
double OptionChainRow::OpenInterest() const
{
	return this->_OpenInterest;
}
double OptionChainRow::ImpliedVol() const
{
	return this->_ImpliedVol;
}
// Mutators:
void OptionChainRow::ParseRow(const std::string& row)
{
	std::istringstream line(row);
	std::string cell;
	std::size_t index = 0;
	while (std::getline(line, cell, ',') && index < 12)
	{
		if (index > 1)
			this->_ParseCell(cell, index);
		++index;
	}
}
// Overloaded Operators:
void OptionChainRow::operator<<(const std::string &row)
{
	this->ParseRow(row);
}
OptionChainRow& OptionChainRow::operator=(const OptionChainRow &row)
{
	if (this != &row)
	{
		this->_Ask = row._Ask;
		this->_Bid = row._Bid;
		this->_Change = row._Change;
		this->_ImpliedVol = row._ImpliedVol;
		this->_LastPrice = row._LastPrice;
		this->_OpenInterest = row._OpenInterest;
		this->_PercentChange = row._PercentChange;
		this->_Strike = row._Strike;
		this->_Volume = row._Volume;
	}
	return *this;
}

// Private Helpers: 
void OptionChainRow::_ParseCell(const std::string &cell, const std::size_t &index)
{
	double val;
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