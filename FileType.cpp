#include "FileType.hpp"

// Private Helpers:
void FileType::_ExtractAttributes(unsigned firstIDX, const std::string &fileName)
{
	this->_ValMonth = std::stoul(fileName.substr(firstIDX + 1, 2));
	this->_ValDay = std::stoul(fileName.substr(firstIDX + 4, 2));
	this->_ValYear = std::stoul(fileName.substr(firstIDX + 7, 4));
}
// Constructors/Destructor:
FileType::FileType() : _Data(), _ValYear(), _ValDay(), _ValMonth()
{

}
FileType::FileType(const FileType * const file) : _Data(file->_Data), _ValYear(file->_ValYear), 
	_ValDay(file->_ValDay), _ValMonth(file->_ValMonth)
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
unsigned FileType::ValueYear() const
{
	return this->_ValYear;
}
unsigned FileType::ValueMonth() const
{
	return this->_ValMonth;
}
unsigned FileType::ValueDay() const
{
	return this->_ValDay;
}
// Interface Methods:
bool FileType::PathExists(const std::string &path) const
{
	if (!std::filesystem::exists(path))
	{
		throw std::exception("valueDateFolder does not exist.");
	}
}
std::string FileType::ValueDateStr() const
{
	std::ostringstream out;
	out << ((this->_ValMonth < 10) ? "0" : "") << this->_ValMonth << "//" <<
		((this->_ValDay < 10) ? "0" : "") << this->_ValDay << "//" << this->_ValYear;
	return out.str();
}
// Overloaded Operators:
FileType& FileType::operator=(const FileType * const file)
{
	if (this != file)
	{
		this->_ValDay = file->_ValDay;
		this->_ValMonth = file->_ValMonth;
		this->_ValYear = file->_ValYear;
		this->_Data = file->_Data;
	}
	return *this;
}