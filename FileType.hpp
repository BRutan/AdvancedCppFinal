#ifndef FILETYPE_HPP
#define FILETYPE_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileRow.hpp"

class FileType
{
protected:
	std::unordered_map<std::string, FileRow*> _Data;
public:
	FileType()
	{

	}
	virtual ~FileType()
	{

	}
	// Accessors:
	std::size_t NumRows() const
	{
		return this->_Data.size();
	}
	// Mutators:
	virtual void ParseFile(const std::string &path) = 0;
	// Interface Methods:
	virtual bool PathExists(const std::string &path)
	{
		if (!std::filesystem::exists(path))
		{
			throw std::exception("valueDateFolder does not exist.");
		}
	}
};

#endif
