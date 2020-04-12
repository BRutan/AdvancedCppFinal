#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include "OptionChainPath.hpp"


OptionChainPath::OptionChainPath() : _Month(0), _Day(0), _Year(0), _ValueDateFolder("")
{

}
OptionChainPath::OptionChainPath(unsigned month, unsigned day, unsigned year, const std::string& valueDateFolder) : 
	_Month(month), _Day(day), _Year(year), _ValueDateFolder(valueDateFolder)
{

}
OptionChainPath::~OptionChainPath()
{

}
// Accessors:
unsigned OptionChainPath::Month() const
{
	return this->_Month;
}
unsigned OptionChainPath::Day() const
{
	return this->_Day;
}
unsigned OptionChainPath::Year() const
{
	return this->_Year;
}
const std::string& OptionChainPath::ValueDateFolder() const
{
	return this->_ValueDateFolder;
}
// Mutators:
void OptionChainPath::Month(unsigned month)
{
	this->_Month = month;
}
void OptionChainPath::Day(unsigned day)
{
	this->_Day = day;
}
void OptionChainPath::Year(unsigned year)
{
	this->_Year = year;
}
void OptionChainPath::ValueDateFolder(const std::string &folderPath)
{
	this->_ValueDateFolder = folderPath;
}
// Interface Methods:
bool OptionChainPath::CreateDirectory() const
{
	try
	{

		return true;
	}
	catch (...)
	{
		return false;
	}
}
bool OptionChainPath::CreateDirectoryTree() const
{
	if (!std::filesystem::exists())
	{

	}
	if (!std::filesystem::exists())
	{

	}
}
bool OptionChainPath::PathExists() const
{
	return std::filesystem::exists(this->Path());
}
std::string OptionChainPath::Path() const
{
	std::stringstream s(this->_ValueDateFolder);
	s << "//" << "";
	return s.str();
}
// Overloaded Operators:
const OptionChainPath& OptionChainPath::operator=(const OptionChainPath& oc)
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