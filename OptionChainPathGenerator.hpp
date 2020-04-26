#ifndef OPTIONCHAINPATHGENERATOR_HPP
#define OPTIONCHAINPATHGENERATOR_HPP

#include <iostream>
#include <filesystem>
#include <ql/time/date.hpp>
#include <sstream>
#include <string>

class OptionChainPathGenerator
{
private:
	static std::unordered_map<unsigned, QuantLib::Month> _MonthToEnum;
	QuantLib::Date _ExpirationDate, _ValueDate;
	std::string _ValueDateFolder, _ExpirationDateFolder, _ContainerFolder;
public:
	// Constructors/Destructor:
	OptionChainPathGenerator(const std::string &containerFolder = "");
	OptionChainPathGenerator(const std::string &expDateFolder, const std::string &valueDateFolder, const std::string &containerFolder = "");
	OptionChainPathGenerator(const QuantLib::Date &expDate, const QuantLib::Date &valueDate, const std::string &containerFolder = "");
	virtual ~OptionChainPathGenerator();
	// Accessors:
	const std::string& ContainerFolder() const;
	const std::string& ExpirationDateFolder() const;
	const QuantLib::Date& ExpirationDate() const;
	const QuantLib::Date& ValueDate() const;
	const std::string& ValueDateFolder() const;
	// Mutators:
	void ContainerFolder(const std::string&);
	void ExpirationDate(const QuantLib::Date&);
	void ValueDate(const QuantLib::Date&);
	// Interface Methods:
	static std::string ExtractTicker(const std::string &chainpath);
	static QuantLib::Date ExtractExpirationDate_Chain(const std::string &chainpath);
	static QuantLib::Date ExtractExpirationDate_Folder(const std::string &chainpath);
	static QuantLib::Date ExtractValueDate(const std::string &chainpath);
	static std::string DateToString(const QuantLib::Date &dt, char delim);
	static QuantLib::Date StringToDate(const std::string &str, char delim);
	bool IsExpDate(const std::string &path) const;
	bool IsValueDate(const std::string &path) const;
	bool PathExists(const std::string &ticker) const;
	std::string TickerPath(const std::string &ticker) const;
	// Overloaded Operators:
	const OptionChainPathGenerator& operator=(const OptionChainPathGenerator&);
};

#endif