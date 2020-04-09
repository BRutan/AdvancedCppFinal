#ifndef OPTIONCHAIN_HPP
#define OPTIONCHAIN_HPP

#include <string>
#include <unordered_map>

class OptionChain
{
private:
	std::unordered_map<std::string, OptionChainRow> _Data;

public:
	OptionChain();
	virtual ~OptionChain();

};

class OptionChainRow
{
private:

public:
	OptionChainRow();
	virtual ~OptionChainRow();

};



#endif
