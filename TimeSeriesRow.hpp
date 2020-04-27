#ifndef TIMESERIESROW_HPP
#define TIMESERIESROW_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "FileRow.hpp"

template<unsigned long numcols>
class TimeSeriesRow : public FileRow
{
private:
	double _Values[numcols];
public:
	// Constructors/Destructor:
	TimeSeriesRow(const std::string &row)
	{
		this->ParseRow(row);
	}
	virtual ~TimeSeriesRow()
	{

	}
	// Accessors:
	double GetTimeSeries(unsigned long index) const
	{
		return this->_Values[index];
	}
	// Mutators:
	void ParseRow(const std::string &line)
	{
		std::istringstream str(line);
		double val;
		unsigned long col = 0;
		std::string cell;
		std::getline(str, cell, ',');
		while (col < numcols && std::getline(str, cell, ','))
		{
			std::istringstream parse(cell);
			this->_Values[col] = (parse >> val) ? val : 0;
			++col;	
		}
	}
	// Overloaded Operators:
	friend std::ostream& operator<<(std::ostream &stream, const TimeSeriesRow &row)
	{
		for (std::size_t col = 0; col < numcols; ++col)
		{
			stream << row._Values[col] << ((col + 1 != numcols) ? "," : "");
		}
		return stream;
	}
	TimeSeriesRow& operator=(const TimeSeriesRow &row)
	{
		if (this != &row)
		{
			unsigned long col = 0;
			while (col < numcols)
			{
				this->_Values[col] = row._Values[col];
			}
		}
		return *this;
	}
	double operator[](unsigned long index) const
	{
		return this->_Values[index];
	}
};

#endif
