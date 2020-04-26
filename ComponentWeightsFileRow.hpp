#ifndef TICKERSFILEROW_HPP
#define TICKERSFILEROW_HPP

#include <sstream>
#include <string>
#include "FileRow.hpp"

class ComponentWeightsFileRow : public FileRow
{
private:
	std::string _Ticker;
	double _Weight, _DivYield;
public:
	// Constructors/Destructor:
	ComponentWeightsFileRow();
	ComponentWeightsFileRow(const std::string &row);
	ComponentWeightsFileRow(const ComponentWeightsFileRow&);
	ComponentWeightsFileRow(const std::string &ticker, double weight, double yield);
	virtual ~ComponentWeightsFileRow();
	// Accessors:
	double DividendYield() const;
	double Weight() const;
	const std::string& Ticker() const;
	// Mutators:
	void ParseRow(const std::string& row);
	// Overloaded Operators:
	ComponentWeightsFileRow& operator=(const ComponentWeightsFileRow &row);
	friend std::ostream& operator<<(std::ostream &stream, const ComponentWeightsFileRow &row)
	{
		stream << row._Ticker << ',' << row._Weight << ',' << row._DivYield;
		return stream;
	}
};

#endif
