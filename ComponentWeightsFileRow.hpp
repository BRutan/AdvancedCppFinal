#ifndef TICKERSFILEROW_HPP
#define TICKERSFILEROW_HPP

#include <sstream>
#include <string>
#include "FileRow.hpp"

class ComponentWeightsFileRow : public FileRow
{
private:
	std::string _Ticker;
	double _Weight;
public:
	// Constructors/Destructor:
	ComponentWeightsFileRow(const std::string &row);
	ComponentWeightsFileRow(const ComponentWeightsFileRow&);
	virtual ~ComponentWeightsFileRow();
	// Accessors:
	const std::string& Ticker() const;
	double Weight() const;
	// Mutators:
	void ParseRow(const std::string& row);
	// Overloaded Operators:
	ComponentWeightsFileRow& operator=(const ComponentWeightsFileRow &row);
};

#endif
