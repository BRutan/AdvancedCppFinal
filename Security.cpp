#include "Security.hpp"
#include "Option.hpp"

static OptionAttributes _DefaultOpt = OptionAttributes();
SecurityAttributes &Security::_Default = _DefaultOpt;

/////////////////
// SecurityAttributes:
/////////////////
// Constructors/Destructor:
SecurityAttributes::SecurityAttributes() : _SettlementDate(), _IsLong(), _Price()
{

}
SecurityAttributes::SecurityAttributes(double price, const QuantLib::Date& settle, bool IsLong) : 
	_SettlementDate(settle), _IsLong(IsLong), _Price((!IsLong) ? -price : price)
{

}
SecurityAttributes::SecurityAttributes(SecurityAttributes &attr) : _SettlementDate(attr._SettlementDate), 
	_IsLong(attr._IsLong), _Price(attr._Price) 
{

}
SecurityAttributes::SecurityAttributes(SecurityAttributes &&attr) : _SettlementDate(std::move(attr._SettlementDate)), 
	_IsLong(std::move(attr._IsLong)), _Price(std::move(attr._IsLong))
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
Security::Security() : _Attributes(Security::_Default)
{

}
Security::Security(SecurityAttributes& attr) : _Attributes(attr)
{

}
Security::Security(Security &sec) : _Attributes(sec._Attributes)
{

}
Security::~Security()
{

}
// Accessors:
SecurityAttributes& Security::Attributes()
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