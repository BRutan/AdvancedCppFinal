
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include "OptionChainPathGenerator.hpp"

// Constructors/Destructor:
OptionChainPathGenerator::OptionChainPathGenerator() : _ExpMonth(0), _ExpDay(0), _ExpYear(0), _ValueDateFolder("")
{

}
OptionChainPathGenerator::OptionChainPathGenerator(unsigned month, unsigned day, unsigned year, 
	const std::string& valueDateFolder) : 
	_ExpMonth(month), _ExpDay(day), _ExpYear(year), _ValueDateFolder(valueDateFolder)
{

}
OptionChainPathGenerator::~OptionChainPathGenerator()
{

}
// Accessors:
unsigned OptionChainPathGenerator::ExpMonth() const
{
	return this->_ExpMonth;
}
unsigned OptionChainPathGenerator::ExpDay() const
{
	return this->_ExpDay;
}
unsigned OptionChainPathGenerator::ExpYear() const
{
	return this->_ExpYear;
}
const std::string& OptionChainPathGenerator::ValueDateFolder() const
{
	return this->_ValueDateFolder;
}
// Mutators:
void OptionChainPathGenerator::Month(unsigned month)
{
	this->_ExpMonth = month;
}
void OptionChainPathGenerator::Day(unsigned day)
{
	this->_ExpDay = day;
}
void OptionChainPathGenerator::Year(unsigned year)
{
	this->_ExpYear = year;
}
void OptionChainPathGenerator::ValueDateFolder(const std::string &folderPath)
{
	this->_ValueDateFolder = folderPath;
}
// Interface Methods:
std::string OptionChainPathGenerator::ExtractTicker(const std::string &chainpath)
{
	auto filepath = chainpath.substr(chainpath.find_last_of("\\", 0));
	return filepath.substr(0, filepath.find_first_of('_'));
}
bool OptionChainPathGenerator::IsExpDate(const std::string &folderPath) const
{
	auto endPath = folderPath.substr(folderPath.find_last_of('\\', 0));
	if (this->_ExpMonth == std::stoi(endPath.substr(4, 2)) && this->_ExpDay == std::stoi(endPath.substr(6, 2)) && this->_ExpYear == std::stoi(endPath.substr(8, 4)))
	{
		return true;
	}
	return false;
}
bool OptionChainPathGenerator::PathExists(const std::string &ticker) const
{
	return std::filesystem::exists(this->TickerPath(ticker));
}
std::string OptionChainPathGenerator::TickerPath(const std::string &ticker) const
{
	std::stringstream s(this->_ValueDateFolder);
	s << "\\" << ticker << "_" << ((this->_ExpMonth < 0) ? "0" : "") << this->_ExpMonth;
	s << "_" << ((this->_ExpDay < 10) ? "0" : "") << this->_ExpDay << "_" << this->_ExpYear;
	return s.str();
}
// Overloaded Operators:
const OptionChainPathGenerator& OptionChainPathGenerator::operator=(const OptionChainPathGenerator& oc)
{
	if (this != &oc)
	{
		this->_ExpDay = oc._ExpDay;
		this->_ExpMonth = oc._ExpMonth;
		this->_ExpYear = oc._ExpYear;
		this->_ValueDateFolder = oc._ValueDateFolder;
	}
	return *this;
}