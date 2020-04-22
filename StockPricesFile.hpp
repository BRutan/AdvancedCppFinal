#ifndef STOCKPRICESFILE_HPP
#define STOCKPRICESFILE_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "FileType.hpp"

class StockPricesFile : FileType
{

public:
	// Constructors/Destructor:
	StockPricesFile(const std::string &path);
	virtual ~StockPricesFile();
	virtual void ParseFile(const std::string &path);
	// Overloaded Operators:
	StockPricesFile& operator=(const StockPricesFile&);
};

#endif
