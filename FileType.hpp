#ifndef FILETYPE_HPP
#define FILETYPE_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileRow.hpp"

class FileType
{
protected:
	std::unordered_map<float, FileRow*> _Data;
public:
	// Constructors/Destructor:
	FileType(): _Data()
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
	virtual bool PathExists(const std::string &path) const
	{
		if (!std::filesystem::exists(path))
		{
			throw std::exception("valueDateFolder does not exist.");
		}
	}
	// Overloaded Operators:
	FileType& operator=(const FileType &file)
	{
		if (this != &file)
		{
			this->_Data = file._Data;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream &stream, const FileType *file)
	{
		for (auto &row : file->_Data)
		{
			stream << row.second << '\n';
		}
		return stream;
	}
};

#endif
