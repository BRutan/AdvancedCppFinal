#ifndef FILETYPECONTAINER_HPP
#define FILETYPECONTAINER_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileType.hpp"

class FileTypeContainer
{
protected:
	std::unordered_map<std::string, FileType*> _Files;
public:
	// Constructor/Destructor:
	FileTypeContainer();
	FileTypeContainer(std::unordered_map<std::string, FileType*> files);
	FileTypeContainer(const FileTypeContainer& cont);
	virtual ~FileTypeContainer();
	// Interface Methods:
	virtual void ParseFiles(const std::string&) = 0;
	virtual bool PathExists(const std::string &path) const;
	// Overloaded Operators:
	FileTypeContainer& operator=(const FileTypeContainer &cont);
};

#endif
