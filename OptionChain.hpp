#ifndef OPTIONCHAIN_HPP
#define OPTIONCHAIN_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include "OptionChainRow.hpp"

class OptionChain
{
private:
	unsigned _ExpYear, _ExpMonth, _ExpDay;
	std::string _Ticker;
	bool _IsCalls;
	// Map Strike -> Row:
	std::unordered_map<float, OptionChainRow> _Rows;
public:
	// Constructors/Destructor:
	OptionChain(const std::string &path);
	virtual ~OptionChain();
	// Accessors:
	const std::string& Ticker() const;
	const std::unordered_map<float, OptionChainRow>& Rows() const;
	// Mutators:
	void ParseFile(const std::string & filepath);
	// Interface Methods:
	std::string ExpDateStr() const;
};

#endif
