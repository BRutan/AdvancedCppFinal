#ifndef FILETYPECONTAINER_HPP
#define FILETYPECONTAINER_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileType.hpp"

class FileTypeContainer
{
protected:
	std::unordered_map<std::string, FileType*> _Files;
public:
	// Constructor/Destructor:
	FileTypeContainer() : _Files()
	{

	}
	FileTypeContainer(const FileTypeContainer& cont) : _Files(cont._Files)
	{

	}
	virtual ~FileTypeContainer()
	{

	}
	// Interface Methods:
	virtual void ParseFiles(const std::string&) = 0;
	virtual bool PathExists(const std::string &path) const
	{
		if (!std::filesystem::exists(path))
		{
			throw std::exception("valueDateFolder does not exist.");
		}
	}
	// Overloaded Operators:
	FileTypeContainer& operator=(const FileTypeContainer &cont)
	{
		if (this != &cont)
		{
			this->_Files = cont._Files;
		}
		return *this;
	}
};

#endif
