
#include "BondFileRow.hpp"


// Constructors/Destructor:
BondFileRow::BondFileRow(const std::string& row)
{
	this->ParseRow(row);
}
BondFileRow::BondFileRow(const BondFileRow &row) : _Tenor(row._Tenor), _Yield(row._Yield)
{

}
BondFileRow::~BondFileRow()
{

}
// Accessors:
double BondFileRow::Tenor() const
{
	return this->_Tenor;
}
double BondFileRow::Yield() const
{
	return this->_Yield;
}
// Interface Methods:
void BondFileRow::ParseRow(const std::string& row)
{
	std::istringstream stream(row);
	std::string cell;
	std::size_t index = 0;
	double val;
	while (std::getline(stream, cell, ',') && index < 2)
	{
		std::istringstream parser(cell);
		switch (index)
		{
		case 0:
			this->_Tenor = (parser >> val) ? val : 0;
			break;
		case 1:
			this->_Yield = (parser >> val) ? val : 0;
			break;
		}
		++index;
	}
}
// Overloaded Operators:
BondFileRow& BondFileRow::operator=(const BondFileRow& row)
{
	if (this != &row)
	{
		this->_Tenor = row._Tenor;
		this->_Yield = row._Yield;
	}
	return *this;
}
