#ifndef FILETYPECONTAINER_HPP
#define FILETYPECONTAINER_HPP

#include <ql/time/date.hpp>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "FileType.hpp"
#include "OptionChainPathGenerator.hpp"

class FileTypeContainer
{
protected:
	std::unordered_map<std::string, FileType*> _Files;
public:
	// Constructor/Destructor:
	FileTypeContainer();
	FileTypeContainer(const std::unordered_map<std::string, FileType*> &files);
	FileTypeContainer(const FileTypeContainer& cont);
	virtual ~FileTypeContainer();
	// Accessors:
	const std::unordered_map<std::string, FileType*>& Files() const;
	// Interface Methods:
	virtual void ParseFiles(const QuantLib::Date &dt) = 0;
	bool PathExists(const std::string &path) const;
	// Overloaded Operators:
	FileTypeContainer& operator=(const FileTypeContainer &cont);
};

#endif
