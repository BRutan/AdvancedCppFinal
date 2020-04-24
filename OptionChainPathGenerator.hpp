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
	unsigned _ExpMonth, _ExpDay, _ExpYear;
	std::string _ValueDateFolder;
public:
	// Constructors/Destructor:
	OptionChainPathGenerator();
	OptionChainPathGenerator(const std::string &expDateFolder, const std::string &valueDateFolder);
	OptionChainPathGenerator(unsigned expMonth, unsigned expDay, unsigned expYear, const std::string& valueDateFolder);
	virtual ~OptionChainPathGenerator();
	// Accessors:
	unsigned ExpMonth() const;
	unsigned ExpDay() const;
	unsigned ExpYear() const;
	std::string ExpDateString() const;
	const std::string& ValueDateFolder() const;
	// Mutators:
	void ExpMonth(unsigned);
	void ExpDay(unsigned);
	void ExpYear(unsigned);
	void ValueDateFolder(const std::string&);
	// Interface Methods:
	static std::string ExtractTicker(const std::string &chainpath);
	static std::tuple<unsigned, unsigned, unsigned> ExtractExpirationDate(const std::string &chainpath);
	static std::tuple<unsigned, unsigned, unsigned> ExtractValueDate(const std::string &chainpath);
	bool IsExpDate(const std::string &path) const;
	bool PathExists(const std::string &ticker) const;
	std::string TickerPath(const std::string &ticker) const;
	// Overloaded Operators:
	const OptionChainPathGenerator& operator=(const OptionChainPathGenerator&);
};

#endif