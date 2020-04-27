#ifndef TIMESERIES_HPP
#define TIMESERIES_HPP

#include <ql/time/date.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "FileType.hpp"
#include "Hashers.hpp"
#include "TimeSeriesRow.hpp"

template<unsigned long numcols>
class TimeSeries
{
private:
	std::string _Symbols[numcols];
	std::unordered_map<std::string, unsigned long> _SymbolsToColumnNum;
	std::unordered_map<QuantLib::Date, TimeSeriesRow<numcols>, QDateHash> _Values;
public:
	// Constructors/Destructor:
	TimeSeries()
	{

	}
	TimeSeries(const std::string &path)
	{
		this->ParseFile(path);
	}
	virtual ~TimeSeries()
	{

	}
	// Accessors:
	std::size_t NumRows() const
	{
		return this->_Values.count();
	}
	const std::string * const Symbols() const
	{
		return this->_Symbols;
	}
	const TimeSeriesRow<numcols>& GetRow(const QuantLib::Date &date) const
	{
		return this->_Values[date];
	}
	std::unordered_map<std::string, double> GetSeriesForDate(const QuantLib::Date &dt) const
	{
		std::unordered_map<std::string, double> output;
		unsigned long col = 0;
		auto row = this->_Values.find(dt);
		while (col < numcols)
		{
			double val = row->second.operator[](col);
			//output.emplace(std::string(this->_Symbols[col]), row->second[col]);
			++col;
		}
		return output;
	}
	const std::unordered_map<QuantLib::Date, TimeSeriesRow<numcols>>& Values() const
	{
		return this->_Values;
	}
	// Mutators:
	virtual void ParseFile(const std::string &path)
	{
		// File must have symbols in first row excluding first column.
		// First column must be a date with format MM/DD/YYYY.
		if (!FileType::PathExists(path))
		{
			throw std::exception("path does not exist.");
		}
		std::ifstream file(path);
		if (!file)
		{
			throw std::exception("Could not open file at path.");
		}
		if (this->_Values.size())
		{
			this->_Values.clear();
			this->_SymbolsToColumnNum.clear();
		}
		unsigned long row = 0, col = 0;
		std::string line, cell;
		QuantLib::Date dt;
		while (!file.eof())
		{
			std::getline(file, line);
			std::istringstream str(line);
			if (row != 0)
			{
				// Get all data:
				std::getline(str, cell,',');
				if (cell.size() <= 1)
				{
					break;
				}
				dt = FileType::StringToDate(cell, '//');
				this->_Values.emplace(dt, TimeSeriesRow<numcols>(line));
			}
			else
			{
				// Get all symbols:
				std::getline(str,cell,',');
				while (col < numcols)
				{
					std::getline(str, cell, ',');
					this->_Symbols[col] = cell;
					this->_SymbolsToColumnNum.emplace(cell, col);
					++col;
				}
			}
			++row;
		}
		file.close();
	}
	// Overloaded Operators:
	friend std::ostream& operator<<(std::ostream &stream, const TimeSeries &series)
	{	
		stream << "Date,";
		for (unsigned long col = 0; col < numcols; ++col)
		{
			stream << series._Symbols[col] << ((col + 1 != numcols) ? "," : "");
		}
		stream << '\n';
		for (auto &line : series._Values)
		{
			stream << FileType::DateToString(line.first, '//') << ',' << line.second << '\n';
		}
		return stream;
	}
	TimeSeries& operator=(const TimeSeries &series)
	{
		if (this != &series)
		{
			this->_Symbols = series._Symbols;
			this->_SymbolsToColumnNum = series._SymbolsToColumnNum;
			this->_Values = series._Values;
		}
		return *this;
	}
};

#endif