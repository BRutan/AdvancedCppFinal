#ifndef BONDFILE_HPP
#define BONDFILE_HPP

#include "BondFileRow.hpp"
#include "FileType.hpp"

class BondFile : FileType
{
public:
	// Constructors/Destructor:
	BondFile(const std::string&path);
	virtual ~BondFile();
	// Interface Methods:
	virtual void ParseRow(const BondFileRow&);
	// Overloaded Operators:
};


#endif
