#ifndef FILETYPE_HPP
#define FILETYPE_HPP

#include <filesystem>
#include <ql/time/date.hpp>
#include <string>
#include <sstream>
#include <unordered_map>
#include "FileRow.hpp"

class FileType
{
protected:
	static std::unordered_map<unsigned, QuantLib::Month> _MonthToEnum;
	std::unordered_map<double, FileRow*> _Data;
	QuantLib::Date _ValueDate;
	void _ExtractAttributes(std::size_t firstIDX, const std::string &fileName);
public:
	// Constructors/Destructor:
	FileType();
	FileType(const FileType * const);
	FileType(const std::unordered_map<double, FileRow*> data);
	virtual ~FileType();
	// Accessors:
	std::size_t NumRows() const;
	const QuantLib::Date& ValueDate() const;
	const std::unordered_map<double, FileRow*> Data() const;
	// Mutators:
	virtual void ParseFile(const std::string &path) = 0;
	// Interface Methods:
	virtual bool HasRow(double key) const;
	std::string ValueDateStr() const;
	static bool PathExists(const std::string &path);
	static QuantLib::Month MonthToEnum(unsigned month);
	static std::string DateToString(const QuantLib::Date &dt, char delim);
	static QuantLib::Date StringToDate(const std::string &str, char delim);
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
