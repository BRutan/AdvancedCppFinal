#ifndef FILEROW_HPP
#define FILEROW_HPP

#include <string>

class FileRow
{
public:
	// Constructors/Destructor:
	FileRow();
	virtual ~FileRow();
	// Mutators:
	virtual void ParseRow(const std::string& row) = 0;
};

#endif
