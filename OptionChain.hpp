#ifndef OPTIONCHAIN_HPP
#define OPTIONCHAIN_HPP

#include <fstream>
#include <ql/time/date.hpp>
#include <ql/time/daycounters/all.hpp>
#include <string>
#include <unordered_map>
#include "OptionChainRow.hpp"
#include "FileType.hpp"

class OptionChain : public FileType
{
private:
	QuantLib::Date _ExpDate;
	std::string _Ticker;
	bool _IsCalls;
	void _ExtractAttributes(const std::string &path);
	static std::string _HeaderString;
public:
	// Constructors/Destructor:
	OptionChain(const std::string &path);
	OptionChain(const OptionChain &chain);
	virtual ~OptionChain();
	// Accessors:
	const QuantLib::Date& ExpirationDate() const;
	const std::string& Ticker() const;
	// Mutators:
	void ParseFile(const std::string & filepath);
	// Interface Methods:
	std::string ExpDateStr() const;
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
	OptionChain& operator=(const OptionChain &chain);
};

#endif
