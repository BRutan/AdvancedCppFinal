#include "Security.hpp"

/////////////////
// SecurityAttributes:
/////////////////
// Constructors/Destructor:
SecurityAttributes::SecurityAttributes(bool IsLong) : _IsLong(IsLong)
{

}
SecurityAttributes::~SecurityAttributes()
{

}
// Accessors:

// Overloaded Operators:
SecurityAttributes& SecurityAttributes::operator=(const SecurityAttributes &attr)
{

}

/////////////////
// Security:
/////////////////
// Constructors/Destructor:
Security::Security(const SecurityAttributes* attr)
{

}
Security::Security(const Security &sec)
{

}
Security::Security(SecurityAttributes &&sec) : _IsLong(sec._IsLong)
{

}
Security::~Security()
{

}
const std::shared_ptr<Security>& Security::Attributes() const
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