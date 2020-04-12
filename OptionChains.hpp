#ifndef OPTIONCHAINS_HPP
#define OPTIONCHAINS_HPP

#include <string>
#include <unordered_map>
#include "OptionChain.hpp"
#include "OptionChainPathGenerator.hpp"

class OptionChains
{
private:
	OptionChainPathGenerator _Generator;
	std::unordered_map<std::string, OptionChain> _Chains;
public:
	OptionChains();
	~OptionChains();


};


#endif
