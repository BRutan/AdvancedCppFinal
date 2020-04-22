#ifndef TICKERSFILE_HPP
#define TICKERSFILE_HPP

#include <fstream>
#include <set>
#include <string>
#include "FileType.hpp"
#include "TickersFileRow.hpp"

class TickersFile : FileType
{
private:
	// All unique tickers in file:
	std::unordered_map<std::string, TickersFileRow> _Tickers;
public:
	// Constructors/Destructor:
	TickersFile(const std::string &path);
	TickersFile(const TickersFile&);
	virtual ~TickersFile();
	// Accessors:
	const std::unordered_map<std::string, TickersFileRow>& Tickers() const;
	// Interface Methods:
	void ParseFile(const std::string &path);
	// Overloaded Operators:
	TickersFile& operator=(const TickersFile&); 
};

#endif
