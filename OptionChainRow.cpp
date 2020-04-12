#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include "OptionChainRow.hpp"

OptionChainRow::OptionChainRow(const std::string& row)
{
	this->ParseRow(row);
}
OptionChainRow::~OptionChainRow()
{

}
// Accessors:
float OptionChainRow::Strike() const
{
	return this->_Strike;
}
float OptionChainRow::LastPrice() const
{
	return this->_LastPrice;
}
float OptionChainRow::Bid() const
{
	return this->_Bid;
}
float OptionChainRow::Ask() const
{
	return this->_Ask;
}
float OptionChainRow::Change() const
{
	return this->_Change;
}
float OptionChainRow::PercentChange() const
{
	return this->_PercentChange;
}
float OptionChainRow::Volume() const
{
	return this->_Volume;
}
float OptionChainRow::OpenInterest() const
{
	return this->_OpenInterest;
}
float OptionChainRow::ImpliedVol() const
{
	return this->_ImpliedVol;
}
// Mutators:
void OptionChainRow::ParseRow(const std::string& row)
{
	std::istringstream line(row), parser;
	std::string cell;
	std::size_t index = 0;
	while (std::getline(line, cell, ',') && index < 12)
	{
		if (index > 1)
			this->_ParseCell(cell, index++);
	}
}
void OptionChainRow::_ParseCell(const std::string &cell, const std::size_t &index)
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
		this->_Change = (stream >> val) ? val : 0;
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
void OptionChainRow::operator<<(const std::string &row)
{
	this->ParseRow(row);
}