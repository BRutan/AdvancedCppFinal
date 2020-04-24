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
	virtual ~SecurityAttributes() = 0;
	// Accessors:
	bool IsLong() const;
	// Overloaded Operators:
	SecurityAttributes& operator=(const SecurityAttributes&);
};

class Security
{
protected:
	std::shared_ptr<SecurityAttributes> _Attributes;
public:
	// Constructors/Destructor:
	Security(const std::shared_ptr<SecurityAttributes>& attr);
	Security(const SecurityAttributes*);
	Security(const Security&);
	virtual ~Security();
	// Accessors:
	virtual double Price() const = 0;
	virtual double Price(const SecurityAttributes*) const = 0;
	const std::shared_ptr<SecurityAttributes>& Attributes() const;
	// Interface Methods:
	virtual double Delta() const = 0;
	// Overloaded Operators:
	Security& operator=(const Security&);
};

#endif