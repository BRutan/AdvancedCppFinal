#include "Security.hpp"

/////////////////
// SecurityAttributes:
/////////////////
// Constructors/Destructor:
SecurityAttributes::SecurityAttributes() : _IsLong(false)
{

}
SecurityAttributes::SecurityAttributes(const QuantLib::Date& settle, bool IsLong) : _IsLong(IsLong)
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
const QuantLib::Date& SecurityAttributes::SettlementDate() const
{
	return this->_SettlementDate;
}
// Mutators:
void SecurityAttributes::IsLong(bool isLong)
{
	this->_IsLong = isLong;
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
		this->_SettlementDate = attr._SettlementDate;
		this->_IsLong = attr._IsLong;
	}
	return *this;
}

/////////////////
// Security:
/////////////////
// Constructors/Destructor:
Security::Security() : _Attributes()
{

}
Security::Security(const std::shared_ptr<SecurityAttributes>& attr) : _Attributes(attr)
{

}
Security::Security(const Security &sec)
{

}
Security::~Security()
{

}
// Accessors:
const std::shared_ptr<SecurityAttributes>& Security::Attributes() const
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