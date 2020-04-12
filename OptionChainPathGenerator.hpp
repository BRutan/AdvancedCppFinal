#ifndef OPTIONCHAINPATHGENERATOR_HPP
#define OPTIONCHAINPATHGENERATOR_HPP

#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

class OptionChainPathGenerator
{
private:
	// Expiration date attributes:
	unsigned _Month, _Day, _Year;
	std::string _ValueDateFolder;
public:
	// Constructors/Destructor:
	OptionChainPathGenerator();
	OptionChainPathGenerator(unsigned month, unsigned day, unsigned year, const std::string& valueDateFolder);
	~OptionChainPathGenerator();
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
	bool PathExists(const std::string &ticker) const;
	std::string Path(const std::string &ticker) const;
	// Overloaded Operators:
	const OptionChainPathGenerator& operator=(const OptionChainPathGenerator&);
};

#endif