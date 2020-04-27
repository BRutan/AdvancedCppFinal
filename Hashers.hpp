#ifndef HASHERS_HPP
#define HASHERS_HPP

#include <ql/time/date.hpp>

struct QDateHash
{
	size_t operator()(const QuantLib::Date& dte) const
	{
		return std::hash<int>{}(dte.serialNumber());
	}
};


#endif
