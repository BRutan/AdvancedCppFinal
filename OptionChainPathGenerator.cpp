
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
	_ContainerFolder()
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const std::string &containerFolder) : _ExpirationDate(), _ValueDate(),
	_ContainerFolder(containerFolder)
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const std::string &expDateFolder, const std::string &valueDateFolder, const std::string &containerFolder) :
	_ContainerFolder(containerFolder)
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const QuantLib::Date &expDate, const QuantLib::Date &valueDate, const std::string &containerFolder) :
	_ExpirationDate(expDate), _ValueDate(valueDate), _ContainerFolder(containerFolder)
{

}
OptionChainPathGenerator::OptionChainPathGenerator(const OptionChainPathGenerator &chain) : _ExpirationDate(chain._ExpirationDate), 
	_ValueDate(chain._ValueDate), _ContainerFolder(chain._ContainerFolder)
{

}
OptionChainPathGenerator::~OptionChainPathGenerator()
{

}
// Accessors:
const std::string& OptionChainPathGenerator::ContainerFolder() const
{
	return this->_ContainerFolder;
}
const QuantLib::Date& OptionChainPathGenerator::ExpirationDate() const
{
	return this->_ExpirationDate;
}
const QuantLib::Date& OptionChainPathGenerator::ValueDate() const
{
	return this->_ValueDate;
}
std::string OptionChainPathGenerator::ExpirationDateFolder() const
{
	std::ostringstream stream(this->ValueDateFolder(), std::ios_base::ate);
	stream << "exp_" << FileType::DateToString(this->_ExpirationDate, '_') << '\\';
	return stream.str().c_str();
}
std::string OptionChainPathGenerator::ValueDateFolder() const
{
	std::ostringstream stream(this->_ContainerFolder, std::ios_base::ate);
	stream << '\\' << FileType::DateToString(this->_ValueDate, '_') << '\\';
	return stream.str().c_str();
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
void OptionChainPathGenerator::ContainerFolder(const std::string &folder)
{
	this->_ContainerFolder = folder;
}
// Interface Methods:
std::string OptionChainPathGenerator::ExtractTicker(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	auto filepath = (index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath;
	return filepath.substr(0, filepath.find_first_of('_'));
}
QuantLib::Date OptionChainPathGenerator::ExtractExpirationDate_Folder(const std::string &chainpath)
{
	auto index = chainpath.rfind('\\');
	std::string fileName((index != chainpath.npos) ? chainpath.substr(index + 1) : chainpath);
	// OptionChainFolders have format exp_<ExpMonth>_<ExpDay>_<ExpYear>:
	index = fileName.find_first_of('_');
	unsigned month = std::stoul(fileName.substr(index + 1, 2));
	index = fileName.find_first_of('_', index + 1);
	QuantLib::Integer day = std::stoul(fileName.substr(index + 1, 2));
	index = fileName.find_first_of('_', index + 1);
	QuantLib::Integer year = std::stoul(fileName.substr(index + 1, 4));
	return QuantLib::Date(day, OptionChainPathGenerator::_MonthToEnum[month], year);
}
QuantLib::Date OptionChainPathGenerator::ExtractExpirationDate_Chain(const std::string &chainpath)
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
std::string OptionChainPathGenerator::DateToString(const QuantLib::Date &dt, char delim)
{
	std::ostringstream str(std::ios_base::app);
	str << ((dt.month() < 10) ? "0" : "") << unsigned(dt.month()) << delim;
	str << ((dt.dayOfMonth() < 10) ? "0" : "") << unsigned(dt.dayOfMonth()) << delim;
	str << ((dt.year() < 1000) ? "0" : "") << unsigned(dt.year());
	return str.str().c_str();
}
QuantLib::Date OptionChainPathGenerator::StringToDate(const std::string &str, char delim)
{
	// Expecing MM<delim>DD<delim>YYYY:
	unsigned month = std::stoul(str.substr(0, 2));
	auto index = str.find_first_of(delim, 0);
	QuantLib::Integer day = std::stoul(str.substr(index + 1, 2));
	index = str.find_first_of(delim, index + 1);
	QuantLib::Integer year = std::stoul(str.substr(index + 1, 4));
	return QuantLib::Date(day, OptionChainPathGenerator::_MonthToEnum[month], year);
}

bool OptionChainPathGenerator::PathExists(const std::string &ticker) const
{
	return std::filesystem::exists(this->TickerPath(ticker));
}
std::string OptionChainPathGenerator::TickerPath(const std::string &ticker) const
{
	std::ostringstream s(this->_ContainerFolder, std::ios_base::ate);
	s << this->ExpirationDateFolder();
	s << ticker << "_" << OptionChainPathGenerator::DateToString(this->_ValueDate, '_') << "_";
	s << OptionChainPathGenerator::DateToString(this->_ExpirationDate, '_') << ".csv";
	return s.str().c_str();
}
// Overloaded Operators:
OptionChainPathGenerator& OptionChainPathGenerator::operator=(const OptionChainPathGenerator& oc)
{
	if (this != &oc)
	{
		this->_ContainerFolder = oc._ContainerFolder;
		this->_ExpirationDate = oc._ExpirationDate;
		this->_ValueDate = oc._ValueDate;		
	}
	return *this;
}