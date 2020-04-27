#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <ql/time/date.hpp>
#include <memory>
#include <iostream>
#include <string>

class EquityAttributes;

class SecurityAttributes
{
protected:
	QuantLib::Date _SettlementDate;
	bool _IsLong;
	double _Price;
public:
	// Constructors/Destructor:
	SecurityAttributes();
	SecurityAttributes(double price, const QuantLib::Date& settle, bool IsLong);
	explicit SecurityAttributes(SecurityAttributes&);
	SecurityAttributes(SecurityAttributes&&);
	virtual ~SecurityAttributes();
	// Accessors:
	bool IsLong() const;
	const QuantLib::Date& SettlementDate() const;
	double Price() const;
	// Mutators:
	void IsLong(bool);
	void Price(double);
	void SettlementDate(const QuantLib::Date&);
	// Overloaded Operators:
	SecurityAttributes& operator=(const SecurityAttributes&);
};

class Security
{
protected:
	static SecurityAttributes &_Default;
	SecurityAttributes& _Attributes;
public:
	// Constructors/Destructor:
	Security();
	Security(SecurityAttributes& attr);
	Security(Security&);
	virtual ~Security();
	// Mutators:
	SecurityAttributes& Attributes();
	// Interface Methods:
	virtual double Price() = 0;
	virtual double Delta() const = 0;
	virtual double Gamma() const = 0;
	virtual double Theta() const = 0;
	virtual double Vega() const = 0;
	virtual double Rho() const = 0;
	// Overloaded Operators:
	Security& operator=(const Security&);
};

#endif