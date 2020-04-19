#ifndef OPTIONCHAINS_HPP
#define OPTIONCHAINS_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
#include "FileType.hpp"
#include "FileTypeContainer.hpp"
#include "OptionChain.hpp"
#include "OptionChainPathGenerator.hpp"

// One set of option chains exists for all tickers in a value date
// folder for a given expiration day, month and year.
class OptionChains : public FileTypeContainer
{
private:
	OptionChainPathGenerator _Generator;
public:
	OptionChains(const std::string &valueDateFolder, unsigned expMonth, unsigned expDay, unsigned expYear) : 
		_Generator(expMonth, expDay, expYear, valueDateFolder),
		FileTypeContainer()
	{
		this->ParseFiles(valueDateFolder);
	}
	virtual ~OptionChains()
	{

	}
	/////////////////
	// Accessors:
	/////////////////
	const std::unordered_map<std::string, FileType*>& GetOptionChains() const
	{
		return FileTypeContainer::_Files;
	}
	bool HasOptionChain(const std::string &ticker) const
	{
		return FileTypeContainer::_Files.find(ticker) == FileTypeContainer::_Files.end();
	}
	const FileType* const GetOptionChain(const std::string &ticker) const
	{
		if (this->HasOptionChain(ticker))
		{
			throw std::exception("Could not find option chain with ticker.");
		}
		return FileTypeContainer::_Files.find(ticker)->second;
	}
	/////////////////
	// Mutators:
	/////////////////
	void ParseFiles(const std::vector<std::string> &tickers)
	{
		// Parse all ticker files for value date and expiration for given tickers:
		if (!this->PathExists(this->_Generator.ValueDateFolder()))
		{
			throw std::exception("valueDateFolder does not exist");
		}
		for (auto &ticker : tickers)
		{
			if (this->_Generator.PathExists(ticker))
			{
				auto path = this->_Generator.TickerPath(ticker);
				FileTypeContainer::_Files.emplace(ticker, &OptionChain(path));
			}
		}
	}
	void ParseFiles(const std::string &valueDateFolder)
	{
		// Pull all option chains in value date folder for given
		// expiration date:
		if (!this->PathExists(valueDateFolder))
		{
			throw std::exception("valueDateFolder does not exist");
		}
		this->_Generator.ValueDateFolder(valueDateFolder);
		// Parse all option chains in the folder matching the expiration
		// date:
		for (const auto &entry : std::filesystem::directory_iterator(valueDateFolder))
		{
			if (this->_Generator.IsExpDate(entry.path().string()))
			{
				// Pull in all option chains from the folder:
				for (const auto &file : std::filesystem::directory_iterator(entry.path().string()))
				{
					auto ticker = this->_Generator.ExtractTicker(file.path().string());
					FileTypeContainer::_Files.emplace(ticker, &OptionChain(file.path().string()));
				}				
			}
		}
	}
	// Overloaded Operators:
	OptionChains& operator=(const OptionChains &chains)
	{
		if (this != &chains)
		{
			FileTypeContainer::operator=(chains);
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream &stream, const OptionChains &chains)
	{
		stream << "ExpirationDate: " << chains._Generator.ExpDateString() << '\n';
		for (auto &chain_pair : chains._Files)
		{
			stream << "Ticker: " << chain_pair.first << '\n';
			stream << chain_pair.second << '\n';
		}
	}
};

#endif
