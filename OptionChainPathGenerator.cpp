
#include <iostream>
#include <filesystem>
#include <limits>
#include <sstream>
#include <string>
#include "OptionChainPathGenerator.hpp"

// Constructors/Destructor:
OptionChainPathGenerator::OptionChainPathGenerator() : _ExpMonth(0), _ExpDay(0), _ExpYear(0), _ValueDateFolder("")
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const std::string &expDateFolder, const std::string &valueDateFolder) :
	_ValueDateFolder(valueDateFolder)
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
void OptionChainPathGenerator::ExpMonth(unsigned month)
{
	this->_ExpMonth = month;
}
void OptionChainPathGenerator::ExpDay(unsigned day)
{
	this->_ExpDay = day;
}
void OptionChainPathGenerator::ExpYear(unsigned year)
{
	this->_ExpYear = year;
}
std::string OptionChainPathGenerator::ExpDateString() const
{
	std::stringstream str;
	str << ((this->_ExpMonth < 10) ? "0" : "") << this->_ExpMonth << "\\";
	str << ((this->_ExpDay < 10) ? "0" : "") << this->_ExpDay << "\\";
	str << this->_ExpYear;
	return str.str();
}
void OptionChainPathGenerator::ValueDateFolder(const std::string &folderPath)
{
	this->_ValueDateFolder = folderPath;
}
// Interface Methods:
std::string OptionChainPathGenerator::ExtractTicker(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	auto filepath = (index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath;
	return filepath.substr(0, filepath.find_first_of('_'));
}
std::tuple<unsigned, unsigned, unsigned> OptionChainPathGenerator::ExtractExpirationDate(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	std::string fileName((index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath);
	// OptionChains have format <Ticker>_<ValueMonth>_<ValueDay>_<ValueYear>_<ExpMonth>_<ExpDay>_<ExpYear>.csv:
	index = fileName.rfind('_');
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	unsigned year = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	unsigned day = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	unsigned month = std::stoul(fileName.substr(index, 2));
	return std::make_tuple(month, day, year);
}
std::tuple<unsigned, unsigned, unsigned> OptionChainPathGenerator::ExtractValueDate(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	std::string fileName((index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath);
	// OptionChains have format <Ticker>_<ValueMonth>_<ValueDay>_<ValueYear>_<ExpMonth>_<ExpDay>_<ExpYear>.csv:	
	index = fileName.find('_');
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	unsigned year = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	unsigned day = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	unsigned month = std::stoul(fileName.substr(index, 2));
	return std::make_tuple(month, day, year);
}
bool OptionChainPathGenerator::IsExpDate(const std::string &folderPath) const
{
	auto index = folderPath.rfind('\\');
	std::string endPath((index != folderPath.npos) ? folderPath.substr(index + 1) : folderPath);
	if (this->_ExpMonth == std::stoul(endPath.substr(4, 2)) 
		&& this->_ExpDay == std::stoul(endPath.substr(7, 2)) 
		&& this->_ExpYear == std::stoul(endPath.substr(10, 4)))
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