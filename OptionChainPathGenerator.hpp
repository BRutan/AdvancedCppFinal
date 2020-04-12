#ifndef OPTIONCHAINPATH_HPP
#define OPTIONCHAINPATH_HPP

#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

class OptionChainPathGenerator
{
private:
	// Expiration date attributes:
	unsigned _Month, _Day, _Year;
	std::string _ValueDateFolder, _Ticker;
public:
	// Constructors/Destructor:
	OptionChainPathGenerator();
	OptionChainPathGenerator(unsigned month, unsigned day, unsigned year, const std::string& valueDateFolder, const std::string & ticker);
	~OptionChainPathGenerator();
	// Accessors:
	unsigned Month() const;
	unsigned Day() const;
	unsigned Year() const;
	const std::string& Ticker() const;
	const std::string& ValueDateFolder() const;
	// Mutators:
	void Month(unsigned);
	void Day(unsigned);
	void Year(unsigned);
	void Ticker(const std::string&);
	void ValueDateFolder(const std::string&);
	// Interface Methods:
	bool PathExists() const;
	std::string Path() const;
	// Overloaded Operators:
	const OptionChainPathGenerator& operator=(const OptionChainPathGenerator&);
	friend std::ostream& operator<<(std::ostream &stream, OptionChainPathGenerator& obj)
	{
		stream << obj.Path();
		return stream;
	}
};

#endif