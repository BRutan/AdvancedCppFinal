#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <ql/time/date.hpp>
#include <memory>
#include <iostream>
#include <string>

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
	virtual ~SecurityAttributes() = 0;
	// Accessors:
	bool IsLong() const;
	const QuantLib::Date& SettlementDate() const;
	double Price() const;
	// Mutators:
	virtual void IsLong(bool);
	void Price(double);
	void SettlementDate(const QuantLib::Date&);
	// Overloaded Operators:
	SecurityAttributes& operator=(const SecurityAttributes&);
};

class Security
{
protected:
	std::shared_ptr<SecurityAttributes> _Attributes;
	QuantLib::Date _ValueDate;
public:
	// Constructors/Destructor:
	Security();
	Security(const std::shared_ptr<SecurityAttributes>& attr);
	Security(const Security&);
	virtual ~Security();
	// Accessors:
	const std::shared_ptr<SecurityAttributes>& Attributes() const;
	const QuantLib::Date& ValueDate() const;
	// Mutators:
	std::shared_ptr<SecurityAttributes>& Attributes_Mutable();
	void ValueDate(const QuantLib::Date&);
	// Interface Methods:
	virtual double Price() const = 0;
	virtual double Delta() const = 0;
	virtual double Gamma() const = 0;
	virtual double Theta() const = 0;
	virtual double Vega() const = 0;
	virtual double Rho() const = 0;
	// Overloaded Operators:
	Security& operator=(const Security&);
};

#endif