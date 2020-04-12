#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include "OptionChainPathGenerator.hpp"

OptionChainPathGenerator::OptionChainPathGenerator() : _Month(0), _Day(0), _Year(0), _ValueDateFolder("")
{

}
OptionChainPathGenerator::OptionChainPathGenerator(unsigned month, unsigned day, unsigned year, 
	const std::string& valueDateFolder) : 
	_Month(month), _Day(day), _Year(year), _ValueDateFolder(valueDateFolder)
{

}
OptionChainPathGenerator::~OptionChainPathGenerator()
{

}
// Accessors:
unsigned OptionChainPathGenerator::Month() const
{
	return this->_Month;
}
unsigned OptionChainPathGenerator::Day() const
{
	return this->_Day;
}
unsigned OptionChainPathGenerator::Year() const
{
	return this->_Year;
}
const std::string& OptionChainPathGenerator::ValueDateFolder() const
{
	return this->_ValueDateFolder;
}
// Mutators:
void OptionChainPathGenerator::Month(unsigned month)
{
	this->_Month = month;
}
void OptionChainPathGenerator::Day(unsigned day)
{
	this->_Day = day;
}
void OptionChainPathGenerator::Year(unsigned year)
{
	this->_Year = year;
}
void OptionChainPathGenerator::ValueDateFolder(const std::string &folderPath)
{
	this->_ValueDateFolder = folderPath;
}
// Interface Methods:
bool OptionChainPathGenerator::PathExists(const std::string &ticker) const
{
	return std::filesystem::exists(this->Path(ticker));
}
std::string OptionChainPathGenerator::Path(const std::string &ticker) const
{
	std::stringstream s(this->_ValueDateFolder);
	s << "//" << "";
	return s.str();
}
// Overloaded Operators:
const OptionChainPathGenerator& OptionChainPathGenerator::operator=(const OptionChainPathGenerator& oc)
{
	if (this != &oc)
	{
		this->_Day = oc._Day;
		this->_Month = oc._Month;
		this->_Year = oc._Year;
		this->_ValueDateFolder = oc._ValueDateFolder;
	}
	return *this;
}