#include "FileType.hpp"


// Constructors/Destructor:
FileType::FileType() : _Data()
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
// Interface Methods:
bool FileType::PathExists(const std::string &path) const
{
	if (!std::filesystem::exists(path))
	{
		throw std::exception("valueDateFolder does not exist.");
	}
}
// Overloaded Operators:
FileType& FileType::operator=(const FileType &file)
{
	if (this != &file)
	{
		this->_Data = file._Data;
	}
	return *this;
}