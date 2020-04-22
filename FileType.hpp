#ifndef FILETYPE_HPP
#define FILETYPE_HPP

#include <filesystem>
#include <string>
#include <sstream>
#include <unordered_map>
#include "FileRow.hpp"

class FileType
{
protected:
	std::unordered_map<double, FileRow*> _Data;
	unsigned _ValYear, _ValMonth, _ValDay;
	void _ExtractAttributes(std::size_t firstIDX, const std::string &fileName);
public:
	// Constructors/Destructor:
	FileType();
	FileType(const FileType * const);
	FileType(const std::unordered_map<double, FileRow*> data);
	virtual ~FileType();
	// Accessors:
	std::size_t NumRows() const;
	unsigned ValueYear() const;
	unsigned ValueMonth() const;
	unsigned ValueDay() const;
	// Mutators:
	virtual void ParseFile(const std::string &path) = 0;
	// Interface Methods:
	virtual bool PathExists(const std::string &path) const;
	std::string ValueDateStr() const;
	static double DateSerial(double);
	// Overloaded Operators:
	FileType& operator=(const FileType * const file);
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
