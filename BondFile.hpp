#ifndef BONDFILE_HPP
#define BONDFILE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "BondFileRow.hpp"
#include "FileType.hpp"

class BondFile : public FileType
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
	
	friend std::ostream& operator<<(std::ostream &stream, const BondFile &file)
	{
		stream << BondFile::_HeaderRow << '\n';
		for (auto &row : file._Data)
		{
			stream << (const BondFileRow*)(row.second) << '\n';
		}
		return stream;
	}
};


#endif
