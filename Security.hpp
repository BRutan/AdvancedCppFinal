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
	// Accessors:

	// Overloaded Operators:
	SecurityAttributes& operator=(const SecurityAttributes&);
};

class Security
{
private:
	std::shared_ptr<SecurityAttributes> _Attributes;
public:
	// Constructors/Destructor:
	Security(const SecurityAttributes*);
	Security(const Security&);
	Security(Security&&);
	virtual ~Security();
	// Accessors:
	virtual double Price() = 0;
	virtual double Price(const SecurityAttributes*) = 0;
	const std::shared_ptr<SecurityAttributes>& Attributes() const;
	// Overloaded Operators:
	Security& operator=(const Security&);
};

#endif