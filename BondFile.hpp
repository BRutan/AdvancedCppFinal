#ifndef BONDFILE_HPP
#define BONDFILE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "BondFileRow.hpp"
#include "FileType.hpp"

class BondFile : FileType
{
private:
	static std::string _HeaderRow;
public:
	// Constructors/Destructor:
	BondFile(const std::string&path);
	virtual ~BondFile();
	// Interface Methods:
	virtual void ParseFile(const std::string &path);
	// Overloaded Operators:
	BondFile& operator=(const BondFile&);
};


#endif
