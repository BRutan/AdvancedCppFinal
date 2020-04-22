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
// Interface Methods:
bool FileTypeContainer::PathExists(const std::string &path) const
{
	if (!std::filesystem::exists(path))
	{
		throw std::exception("valueDateFolder does not exist.");
	}
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