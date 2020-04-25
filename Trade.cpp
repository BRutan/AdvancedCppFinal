#include "Trade.hpp"

Trade::Trade(const std::shared_ptr<SecurityAttributes> attr) : _Attributes(attr)
{

}
Trade::~Trade()
{

}
// Accessors:
std::shared_ptr<SecurityAttributes> Trade::Attributes() const
{
	return this->_Attributes;
}
// Overloaded Operators:
Trade& Trade::operator=(const Trade &trade)
{
	if (this != &trade)
	{
		this->_Attributes = trade._Attributes;
	}
	return *this;
}