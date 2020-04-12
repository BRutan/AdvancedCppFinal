#ifndef OPTIONCHAINPATH_HPP
#define OPTIONCHAINPATH_HPP

#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

class OptionChainPath
{
private:
	// Expiration date attributes:
	unsigned _Month, _Day, _Year;
	std::string _ValueDateFolder;
public:
	// Constructors/Destructor:
	OptionChainPath();
	OptionChainPath(unsigned month, unsigned day, unsigned year, const std::string& valueDateFolder);
	~OptionChainPath();
	// Accessors:
	unsigned Month() const;
	unsigned Day() const;
	unsigned Year() const;
	const std::string& ValueDateFolder() const;
	// Mutators:
	void Month(unsigned);
	void Day(unsigned);
	void Year(unsigned);
	void ValueDateFolder(const std::string&);
	// Interface Methods:
	bool CreateDirectory() const;
	bool CreateDirectoryTree() const;
	bool PathExists() const;
	std::string Path() const;
	// Overloaded Operators:
	const OptionChainPath& operator=(const OptionChainPath&);
	friend std::ostream& operator<<(std::ostream &stream, OptionChainPath& obj)
	{
		stream << obj.Path();
		return stream;
	}
};

#endif