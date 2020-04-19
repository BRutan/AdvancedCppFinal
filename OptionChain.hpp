#ifndef OPTIONCHAIN_HPP
#define OPTIONCHAIN_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include "OptionChainRow.hpp"
#include "FileType.hpp"

class OptionChain : public FileType
{
private:
	unsigned _ExpYear, _ExpMonth, _ExpDay;
	unsigned _ValYear, _ValMonth, _ValDay;
	std::string _Ticker;
	bool _IsCalls;
	void _ExtractAttributes(const std::string &path)
	{
		auto index = path.rfind('\\');
		std::string fileName((index != path.npos) ? path.substr(index + 1) : path);
		auto firstIDX = fileName.find_first_of('_');
		this->_Ticker = fileName.substr(0, firstIDX);
		this->_ValMonth = std::stoul(fileName.substr(firstIDX + 1, 2));
		this->_ValDay = std::stoul(fileName.substr(firstIDX + 4, 2));
		this->_ValYear = std::stoul(fileName.substr(firstIDX + 7, 4));
		this->_ExpMonth = std::stoul(fileName.substr(firstIDX + 12, 2));
		this->_ExpDay = std::stoul(fileName.substr(firstIDX + 15, 2));
		this->_ExpYear = std::stoul(fileName.substr(firstIDX + 18, 4));
	}
	static std::string _HeaderString;
public:
	// Constructors/Destructor:
	OptionChain(const std::string &path) : FileType(), _ExpYear(), _ExpMonth(), _ExpDay(), 
		_ValYear(), _ValMonth(), _ValDay(),_Ticker()
	{
		this->ParseFile(path);
		this->_ExtractAttributes(path);
	}
	virtual ~OptionChain()
	{

	}
	// Accessors:
	unsigned ExpYear() const
	{
		return this->_ExpYear;
	}
	unsigned ExpDay() const
	{
		return this->_ExpDay;
	}
	unsigned ExpMonth() const
	{
		return this->_ExpMonth;
	}
	const std::string& Ticker() const
	{
		return this->_Ticker;
	}
	// Mutators:
	void ParseFile(const std::string & filepath)
	{
		if (this->_Data.size())
		{
			this->_Data.clear();
			this->_IsCalls = false;
		}
		if (filepath.substr(filepath.length() - 10, 10) == "_Calls.csv")
		{
			this->_IsCalls = true;
		}
		std::ifstream file(filepath);
		if (!file)
		{
			throw std::exception("Could not open file.");
		}
		std::string row;
		std::getline(file, row);
		while (!file.eof())
		{
			std::getline(file, row);
			auto newRow = new OptionChainRow(row);
			this->_Data.emplace(newRow->Strike(), newRow);
		}
		file.close();
	}
	// Interface Methods:
	std::string ExpDateStr() const
	{
		std::ostringstream out;
		out << ((this->_ExpMonth < 10) ? "0" : "") << this->_ExpMonth << "//" <<
			((this->_ExpDay < 10) ? "0" : "") << this->_ExpDay << "//" << this->_ExpYear;
		return out.str();
	}
	std::string ValueDateStr() const
	{
		std::ostringstream out;
		out << ((this->_ValMonth < 10) ? "0" : "") << this->_ValMonth << "//" << 
			((this->_ValDay < 10) ? "0" : "") << this->_ValDay << "//" << this->_ValYear;
		return out.str();
	}
	// Overloaded Operators:
	friend std::ostream& operator<<(std::ostream &stream, const OptionChain &chain)
	{
		stream << OptionChain::_HeaderString << '\n';
		for (const auto &row : chain._Data)
		{
			stream << *((OptionChainRow*)row.second) << '\n';
		}
		return stream;
	}
	OptionChain& operator=(const OptionChain &chain)
	{
		if (this != &chain)
		{
			this->_ExpDay = chain._ExpDay;
			this->_ExpMonth = chain._ExpMonth;
			this->_ExpYear = chain._ExpYear;
			this->_IsCalls = chain._IsCalls;
			this->_Ticker = chain._Ticker;
			FileType::operator=(chain);
		}
		return *this;
	}
};

std::string OptionChain::_HeaderString = "Strike,LastPrice,Bid,Ask,Change,PercentChange,Volume,OpenInterest,ImpliedVol";

#endif
