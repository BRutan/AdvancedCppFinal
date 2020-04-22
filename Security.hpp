#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <memory>
#include <iostream>
#include <string>

class SecurityAttributes
{
private:
	bool _IsLong;
public:
	// Constructors/Destructor:
	SecurityAttributes(bool IsLong);
	virtual ~SecurityAttributes();
	// Overloaded Operators:
	SecurityAttributes& operator=(const SecurityAttributes&);
};

class Security
{
private:
	SecurityAttributes* attributes;
public:
	// Constructors/Destructor:
	Security(const SecurityAttributes*);
	Security(const Security&);
	Security(Security&&);
	virtual ~Security();
	virtual double Price() = 0;
	virtual double Price(const SecurityAttributes*) = 0;
	Security& operator=(const Security&);
};

#endif
