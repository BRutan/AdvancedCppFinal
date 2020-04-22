#ifndef FILETYPE_HPP
#define FILETYPE_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileRow.hpp"

class FileType
{
protected:
	std::unordered_map<double, FileRow*> _Data;
public:
	// Constructors/Destructor:
	FileType();
	FileType(const std::unordered_map<double, FileRow*> data);
	virtual ~FileType();
	// Accessors:
	std::size_t NumRows() const;
	// Mutators:
	virtual void ParseFile(const std::string &path) = 0;
	// Interface Methods:
	virtual bool PathExists(const std::string &path) const;
	// Overloaded Operators:
	FileType& operator=(const FileType &file);
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
