#include "FileType.hpp"


std::unordered_map<unsigned, QuantLib::Month> FileType::_MonthToEnum =
{
	{1, QuantLib::January},{2, QuantLib::February},{3, QuantLib::March},{4, QuantLib::April},
	{5, QuantLib::May},{6, QuantLib::June},{7, QuantLib::July},{8, QuantLib::August},
	{9, QuantLib::September},{10, QuantLib::October},{11, QuantLib::November},{12, QuantLib::December}
};

// Private Helpers:
void FileType::_ExtractAttributes(std::size_t firstIDX, const std::string &fileName)
{
	auto month = std::stoul(fileName.substr(firstIDX + 1, 2));
	auto day = std::stoul(fileName.substr(firstIDX + 4, 2));
	auto year = std::stoul(fileName.substr(firstIDX + 7, 4));
	this->_ValueDate = QuantLib::Date(day, FileType::_MonthToEnum[month], year);
}
// Constructors/Destructor:
FileType::FileType() : _Data(), _ValueDate()
{

}
FileType::FileType(const FileType * const file) : _Data(file->_Data), _ValueDate(file->_ValueDate)
{

}
FileType::FileType(const std::unordered_map<double, FileRow*> data) : _Data(data)
{

}
FileType::~FileType()
{

}
// Accessors:
std::size_t FileType::NumRows() const
{
	return this->_Data.size();
}
const QuantLib::Date& FileType::ValueDate() const
{
	return this->_ValueDate;
}
const std::unordered_map<double, FileRow*> FileType::Data() const
{
	return this->_Data;
}
// Interface Methods:
bool FileType::PathExists(const std::string &path)
{
	return std::filesystem::exists(path);
}
std::string FileType::ValueDateStr() const
{
	return FileType::DateToString(this->_ValueDate,'//');
}
std::string FileType::DateToString(const QuantLib::Date &dt, char delim)
{
	std::ostringstream str(std::ios_base::app);
	str << ((unsigned(dt.month()) < 10) ? "0" : "") << unsigned(dt.month()) << delim;
	str << ((unsigned(dt.dayOfMonth()) < 10) ? "0" : "") << dt.dayOfMonth() << delim;
	str << ((unsigned(dt.year()) < 1000) ? "0" : "") << unsigned(dt.year());
	return str.str().c_str();
}
QuantLib::Date FileType::StringToDate(const std::string &str, char delim)
{
	// Expecing MM or M<delim>DD or D<delim>YYYY or YY:
	unsigned firstIndex = str.find_first_of(delim);
	unsigned middleIndex = str.find_first_of(delim, firstIndex + 1);
	QuantLib::Integer month = std::stoul(str.substr(0, std::min<unsigned>(firstIndex, 2)));
	QuantLib::Integer day = std::stoul(str.substr(firstIndex + 1, std::min<unsigned>(middleIndex - firstIndex - 1, 2)));
	QuantLib::Integer year = std::stoul(str.substr(middleIndex + 1, std::max<unsigned>(str.size() - middleIndex - 1, 2)));
	return QuantLib::Date(day, FileType::_MonthToEnum[month], year);
}
QuantLib::Month FileType::MonthToEnum(unsigned month)
{
	return FileType::_MonthToEnum[month];
}
// Overloaded Operators:
FileType& FileType::operator=(const FileType * const file)
{
	if (this != file)
	{
		this->_ValueDate = file->_ValueDate;
		this->_Data = file->_Data;
	}
	return *this;
}