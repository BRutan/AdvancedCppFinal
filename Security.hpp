#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <iostream>
#include <string>

class Security
{
private:

public:
	Security();
	Security(const Security&);
	Security(Security&&);
	virtual ~Security();
	virtual void FromData(const std::string&) = 0;
	Security& operator=(const Security&);
};

#endif
