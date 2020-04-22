#include "TickersFileRow.hpp"

// Constructors/Destructor:
TickersFileRow::TickersFileRow(const std::string &row) : _Ticker(), _Weight()
{

}
TickersFileRow::TickersFileRow(const TickersFileRow&)
{

}
TickersFileRow::~TickersFileRow()
{

}
// Accessors:
const std::string& TickersFileRow::Ticker() const
{
	return this->_Ticker;
}
double TickersFileRow::Weight() const
{
	return this->_Weight;
}
// Mutators:
void TickersFileRow::ParseRow(const std::string& row)
{
	std::istringstream row_str(row);
	std::string cell;
	std::size_t index = 0;
	double weight;
	while (std::getline(row_str, cell, ',') && index < 2)
	{
		switch (index)
		{
		case 0:
			this->_Ticker = cell;
			break;
		case 1:
			std::istringstream str(cell);
			this->_Weight = ((str >> weight) ? weight : 0);
			break;
		}
		++index;
	}
}
// Overloaded Operators:
TickersFileRow& TickersFileRow::operator=(const TickersFileRow &row)
{
	if (this != &row)
	{
		this->_Ticker = row._Ticker;
		this->_Weight = row._Weight;
	}
	return *this;
}