#include "ComponentWeightsFileRow.hpp"

// Constructors/Destructor:
ComponentWeightsFileRow::ComponentWeightsFileRow(const std::string &row) : _Ticker(), _Weight(), _DivYield()
{
	this->ParseRow(row);
}
ComponentWeightsFileRow::ComponentWeightsFileRow(const ComponentWeightsFileRow &row) : _Ticker(row._Ticker), _Weight(row._Weight)
{

}
ComponentWeightsFileRow::~ComponentWeightsFileRow()
{

}
// Accessors:
double ComponentWeightsFileRow::DividendYield() const
{
	return this->_DivYield;
}
const std::string& ComponentWeightsFileRow::Ticker() const
{
	return this->_Ticker;
}
double ComponentWeightsFileRow::Weight() const
{
	return this->_Weight;
}
// Mutators:
void ComponentWeightsFileRow::ParseRow(const std::string& row)
{
	std::istringstream row_str(row);
	std::string cell;
	std::size_t index = 0;
	double val;
	while (std::getline(row_str, cell, ',') && index < 3)
	{
		std::istringstream str(cell);
		switch (index)
		{
		case 0:
			this->_Ticker = cell;
			break;
		case 1:
			this->_Weight = ((str >> val) ? val : 0);
			break;
		case 2:
			this->_DivYield = ((str >> val) ? val : 0);
			break;
		}
		++index;
	}
}
// Overloaded Operators:
ComponentWeightsFileRow& ComponentWeightsFileRow::operator=(const ComponentWeightsFileRow &row)
{
	if (this != &row)
	{
		this->_Ticker = row._Ticker;
		this->_Weight = row._Weight;
	}
	return *this;
}