#ifndef OPTIONCHAINS_HPP
#define OPTIONCHAINS_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
#include "FileType.hpp"
#include "OptionChain.hpp"
#include "OptionChainPathGenerator.hpp"

// One set of option chains exists for all tickers in a value date
// folder for a given expiration day, month and year.
class OptionChains : public FileType
{
private:
	OptionChainPathGenerator _Generator;
	// Map Ticker -> OptionChain for value date.
	std::unordered_map<std::string, OptionChain> _Chains;
public:
	OptionChains(const std::string &valueDateFolder, unsigned expMonth, unsigned expDay, unsigned expYear) : _Generator(expMonth, expDay, expYear, valueDateFolder),
		_Chains()
	{
		this->ParseFile(valueDateFolder);
	}
	virtual ~OptionChains()
	{

	}
	/////////////////
	// Accessors:
	/////////////////
	const OptionChain& GetOptionChain(const std::string &ticker)
	{
		if (this->_Chains.find(ticker) == this->_Chains.end())
		{
			throw std::exception();
		}
		return this->_Chains.find(ticker)->second;
	}
	/////////////////
	// Mutators:
	/////////////////
	void ParseFiles(const std::string &valueDateFolder, const std::vector<std::string> &tickers)
	{
		// Parse all ticker files for value date and expiration for given tickers:
		if (!this->PathExists(valueDateFolder))
		{
			throw std::exception("valueDateFolder does not exist");
		}
		for (auto &ticker : tickers)
		{
			if (this->_Generator.PathExists(ticker))
			{
				auto path = this->_Generator.TickerPath(ticker);
				this->_Chains.emplace(ticker, OptionChain(path));
			}
		}
	}
	void ParseFile(const std::string &valueDateFolder)
	{
		// Pull all option chains in value date folder for given
		// expiration date:
		if (!this->PathExists(valueDateFolder))
		{
			throw std::exception("valueDateFolder does not exist");
		}
		// Parse all option chains in the folder matching the expiration
		// date:
		for (const auto &entry : std::filesystem::directory_iterator(valueDateFolder))
		{
			if (this->_Generator.IsExpDate(entry.path().string()))
			{
				auto ticker = this->_Generator.ExtractTicker(entry.path().string());
				this->_Chains.emplace(ticker, OptionChain(entry.path().string()));
			}
		}
	}
};

#endif
