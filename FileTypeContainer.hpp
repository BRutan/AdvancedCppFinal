#ifndef FILETYPECONTAINER_HPP
#define FILETYPECONTAINER_HPP

#include "FileType.hpp"

class FileTypeContainer
{
public:
	FileTypeContainer()
	{

	}
	virtual ~FileTypeContainer()
	{

	}
	virtual void ParseFiles(const std::string&) = 0;
};


#endif
