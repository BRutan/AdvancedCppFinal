#ifndef TICKERSFILE_HPP
#define TICKERSFILE_HPP

#include <set>
#include <string>
#include "FileType.hpp"

class TickersFile : FileType
{
private:
	std::set<std::string> _Tickers;
public:
	// Constructors/Destructor:
	TickersFile();
	virtual ~TickersFile();
	
	// Overloaded Operators:
	TickersFile& operator=(const TickersFile&); 
};

#endif
