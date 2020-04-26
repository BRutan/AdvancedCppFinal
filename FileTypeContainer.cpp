#include "FileTypeContainer.hpp"

// Constructor/Destructor:
FileTypeContainer::FileTypeContainer() : _Files()
{

}
FileTypeContainer::FileTypeContainer(const FileTypeContainer& cont) : _Files(cont._Files)
{

}
FileTypeContainer::FileTypeContainer(const std::unordered_map<std::string, FileType*> &files) : _Files(files)
{

}
FileTypeContainer::~FileTypeContainer()
{

}
// Accessors:
const std::unordered_map<std::string, FileType*>& FileTypeContainer::Files() const
{
	return this->_Files;
}
// Interface Methods:
bool FileTypeContainer::PathExists(const std::string &path) const
{
	return std::filesystem::exists(path);
}
// Overloaded Operators:
FileTypeContainer& FileTypeContainer::operator=(const FileTypeContainer &cont)
{
	if (this != &cont)
	{
		this->_Files = cont._Files;
	}
	return *this;
}