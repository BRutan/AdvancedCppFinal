#ifndef OPTION_HPP
#define OPTION_HPP

#include "Derivative.hpp"
#include "Security.hpp"

class Option : public Derivative
{
private:

public:
	Option();
	virtual ~OptionChain();

	Option& operator=(const Option&);
};


#endif
