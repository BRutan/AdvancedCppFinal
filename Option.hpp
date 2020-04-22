#ifndef OPTION_HPP
#define OPTION_HPP

#include "OptionChainRow.hpp"
#include "Derivative.hpp"
#include "Security.hpp"

class OptionAttributes : public SecurityAttributes
{
private:
	double _Strike, _Price, _ImpliedVol;
	bool _Long, _Call;
public:
	// Constructors/Destructor:
	OptionAttributes(bool isCall, bool isLong, const OptionChainRow& row);
	virtual ~OptionAttributes();
	// Overloaded Operators:
	OptionAttributes& operator=(const OptionAttributes&);
};

class Option : public Derivative
{
public:
	// Constructors/Destructor:
	Option(const OptionAttributes& attr);
	Option(bool isCall, bool isLong, const OptionChainRow& row);
	virtual ~Option();

	// Overloaded Operators:
	Option& operator=(const Option&);
};


#endif
