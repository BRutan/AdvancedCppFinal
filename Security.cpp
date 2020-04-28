#include "Security.hpp"

/////////////////
// SecurityAttributes:
/////////////////
// Constructors/Destructor:
SecurityAttributes::SecurityAttributes() : _SettlementDate(), _IsLong(false), _Price(0)
{

}
SecurityAttributes::SecurityAttributes(double price, const QuantLib::Date& settle, bool IsLong) : 
	_SettlementDate(settle), _IsLong(IsLong), _Price((!IsLong) ? -price : price)
{

}
SecurityAttributes::~SecurityAttributes()
{

}
// Accessors
bool SecurityAttributes::IsLong() const
{
	return this->_IsLong;
}
double SecurityAttributes::Price() const
{
	return this->_Price;
}
const QuantLib::Date& SecurityAttributes::SettlementDate() const
{
	return this->_SettlementDate;
}
// Mutators:
void SecurityAttributes::IsLong(bool isLong)
{
	this->_IsLong = isLong;
}
void SecurityAttributes::Price(double price)
{
	this->_Price = price;
}
void SecurityAttributes::SettlementDate(const QuantLib::Date& dt)
{
	this->_SettlementDate = dt;
}
// Overloaded Operators:
SecurityAttributes& SecurityAttributes::operator=(const SecurityAttributes &attr)
{
	if (this != &attr)
	{
		this->_IsLong = attr._IsLong;
		this->_SettlementDate = attr._SettlementDate;
		this->_Price = attr._Price;
	}
	return *this;
}

/////////////////
// Security:
/////////////////
// Constructors/Destructor:
Security::Security() : _Attributes(nullptr), _ValueDate()
{

}
Security::Security(const std::shared_ptr<SecurityAttributes>& attr) : _Attributes(attr), _ValueDate()
{

}
Security::Security(const Security &sec) : _Attributes(sec._Attributes), _ValueDate(sec._ValueDate)
{

}
Security::~Security()
{

}
// Accessors:
const QuantLib::Date& Security::ValueDate() const
{
	return this->_ValueDate;
}
const std::shared_ptr<SecurityAttributes>& Security::Attributes() const
{
	return this->_Attributes;
}
// Mutators:
void Security::ValueDate(const QuantLib::Date &dt)
{
	this->_ValueDate = dt;
}
std::shared_ptr<SecurityAttributes>& Security::Attributes_Mutable()
{
	return this->_Attributes;
}
// Overloaded Operators:
Security& Security::operator=(const Security& sec)
{
	if (this != &sec)
	{
		this->_Attributes = sec._Attributes;
	}
	return *this;
}