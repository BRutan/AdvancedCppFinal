
#include <iostream>
#include <filesystem>
#include <limits>
#include <sstream>
#include <string>
#include "OptionChainPathGenerator.hpp"

std::unordered_map<unsigned, QuantLib::Month> OptionChainPathGenerator::_MonthToEnum =
{
	{1, QuantLib::January},{2, QuantLib::February},{3, QuantLib::March},{4, QuantLib::April},
	{5, QuantLib::May},{6, QuantLib::June},{7, QuantLib::July},{8, QuantLib::August},
	{9, QuantLib::September},{10, QuantLib::October},{11, QuantLib::November},{12, QuantLib::December}
};

// Constructors/Destructor:
OptionChainPathGenerator::OptionChainPathGenerator() : _ExpirationDate(), _ValueDate(), 
	_ExpirationDateFolder(), _ValueDateFolder()
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const std::string &expDateFolder, const std::string &valueDateFolder) :
	_ExpirationDateFolder(expDateFolder), _ValueDateFolder(valueDateFolder)
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const QuantLib::Date &expDate, const QuantLib::Date &valueDate) :
	_ExpirationDate(expDate), _ValueDate(valueDate), _ExpirationDateFolder(OptionChainPathGenerator::DateToString(expDate, '_')),
	_ValueDateFolder(OptionChainPathGenerator::DateToString(valueDate,'_'))
{

}
OptionChainPathGenerator::~OptionChainPathGenerator()
{

}
// Accessors:
const QuantLib::Date& OptionChainPathGenerator::ExpirationDate() const
{
	return this->_ExpirationDate;
}
const QuantLib::Date& OptionChainPathGenerator::ValueDate() const
{
	return this->_ValueDate;
}
const std::string& OptionChainPathGenerator::ExpirationDateFolder() const
{
	return this->_ExpirationDateFolder;
}
const std::string& OptionChainPathGenerator::ValueDateFolder() const
{
	return this->_ValueDateFolder;
}
// Mutators:
void OptionChainPathGenerator::ExpirationDate(const QuantLib::Date &exp)
{
	this->_ExpirationDate = exp;
}
void OptionChainPathGenerator::ValueDate(const QuantLib::Date &vd)
{
	this->_ValueDate = vd;
}
void OptionChainPathGenerator::ExpirationDateFolder(const std::string &expf)
{
	this->_ExpirationDateFolder = expf;
	this->_ExpirationDate = OptionChainPathGenerator::StringToDate(expf, '_');
}
void OptionChainPathGenerator::ValueDateFolder(const std::string &vdf)
{
	this->_ValueDateFolder = vdf;
}
// Interface Methods:
std::string OptionChainPathGenerator::ExtractTicker(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	auto filepath = (index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath;
	return filepath.substr(0, filepath.find_first_of('_'));
}
QuantLib::Date OptionChainPathGenerator::ExtractExpirationDate(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	std::string fileName((index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath);
	// OptionChains have format <Ticker>_<ValueMonth>_<ValueDay>_<ValueYear>_<ExpMonth>_<ExpDay>_<ExpYear>.csv:
	index = fileName.rfind('_');
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	QuantLib::Integer year = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	QuantLib::Integer day = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.rfind('_', index);
	unsigned month = std::stoul(fileName.substr(index, 2));
	return QuantLib::Date(day, OptionChainPathGenerator::_MonthToEnum[month], year);
}
QuantLib::Date OptionChainPathGenerator::ExtractValueDate(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	std::string fileName((index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath);
	// OptionChains have format <Ticker>_<ValueMonth>_<ValueDay>_<ValueYear>_<ExpMonth>_<ExpDay>_<ExpYear>.csv:	
	index = fileName.find('_');
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	QuantLib::Integer year = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	QuantLib::Integer day = std::stoul(fileName.substr(index, 2));
	fileName = fileName.substr(0, index);
	index = chainpath.find('_', index);
	unsigned month = std::stoul(fileName.substr(index, 2));
	return QuantLib::Date(day, OptionChainPathGenerator::_MonthToEnum[month], year);
}
bool OptionChainPathGenerator::IsExpDate(const std::string &folderPath) const
{
	auto index = folderPath.rfind('\\');
	std::string endPath((index != folderPath.npos) ? folderPath.substr(index + 1) : folderPath);
	if (this->_ExpirationDate == OptionChainPathGenerator::StringToDate(folderPath, '_'))
	{
		return true;
	}
	return false;
}
std::string OptionChainPathGenerator::DateToString(const QuantLib::Date dt, char delim)
{
	std::stringstream str;
	str << ((dt.month() < 10) ? "0" : "") << dt.month() << delim;
	str << ((dt.dayOfMonth() < 10) ? "0" : "") << dt.dayOfMonth() << delim;
	str << ((dt.year() < 1000) ? "0" : "") << dt.year();
	return str.str();
}
QuantLib::Date OptionChainPathGenerator::StringToDate(const std::string &str, char delim)
{
	// Expecing MM<delim>DD<delim>YYYY:
	auto index = str.find_first_of(delim);
	unsigned month = std::stoul(str.substr(index, 2));
	index = str.find_first_of(delim, index);
	QuantLib::Integer day = std::stoul(str.substr(index, 2));
	index = str.find_first_of(delim, index);
	QuantLib::Integer year = std::stoul(str.substr(index, 2));
	return QuantLib::Date(day, OptionChainPathGenerator::_MonthToEnum[month], year);
}

bool OptionChainPathGenerator::PathExists(const std::string &ticker) const
{
	return std::filesystem::exists(this->TickerPath(ticker));
}
std::string OptionChainPathGenerator::TickerPath(const std::string &ticker) const
{
	std::stringstream s(this->_ValueDateFolder);
	s << "\\" << this->_ExpirationDateFolder << "\\";
	s << ticker << "_" << OptionChainPathGenerator::DateToString(this->_ValueDate, '_') << "_";
	s << OptionChainPathGenerator::DateToString(this->_ExpirationDate, '_') << ".csv";
	return s.str();
}
// Overloaded Operators:
const OptionChainPathGenerator& OptionChainPathGenerator::operator=(const OptionChainPathGenerator& oc)
{
	if (this != &oc)
	{
		this->_ExpirationDate = oc._ExpirationDate;
		this->_ExpirationDateFolder = oc._ExpirationDateFolder;
		this->_ValueDate = oc._ValueDate;
		this->_ValueDateFolder = oc._ValueDateFolder;
	}
	return *this;
}