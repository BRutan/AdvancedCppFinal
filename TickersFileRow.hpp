#ifndef TICKERSFILEROW_HPP
#define TICKERSFILEROW_HPP

#include <sstream>
#include <string>
#include "FileRow.hpp"

class TickersFileRow : public FileRow
{
private:
	std::string _Ticker;
	double _Weight;
public:
	// Constructors/Destructor:
	TickersFileRow(const std::string &row);
	TickersFileRow(const TickersFileRow&);
	virtual ~TickersFileRow();
	// Accessors:
	const std::string& Ticker() const;
	double Weight() const;
	// Mutators:
	void ParseRow(const std::string& row);
	// Overloaded Operators:
	TickersFileRow& operator=(const TickersFileRow &row);
};

#endif
