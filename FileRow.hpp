#ifndef FILEROW_HPP
#define FILEROW_HPP

#include <string>

class FileRow
{
public:
	FileRow();
	virtual ~FileRow();
	virtual void ParseRow(const std::string& row) = 0;
};

#endif
