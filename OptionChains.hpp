#ifndef OPTIONCHAINS_HPP
#define OPTIONCHAINS_HPP

#include <filesystem>
#include <ql/time/date.hpp>
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
	// Constructors/Destructor:
	OptionChains(const std::string &containerFolder = "");
	OptionChains(const QuantLib::Date &valueDate, const std::string &containerFolder = "");
	OptionChains(const QuantLib::Date &expDate, const QuantLib::Date &valueDate, const std::string &containerFolder = "");
	OptionChains(const OptionChainPathGenerator &gen);
	explicit OptionChains(const OptionChains&);
	virtual ~OptionChains();
	// Accessors:
	const std::unordered_map<std::string, FileType*>& GetOptionChains() const;
	bool HasOptionChain(const std::string &ticker) const;
	const OptionChain* const GetOptionChain(const std::string &ticker) const;
	// Mutators:
	void ParseFiles(const std::vector<std::string> &tickers, const QuantLib::Date &expDate);
	void ParseFiles(const QuantLib::Date &expDate);
	// Overloaded Operators:
	OptionChains& operator=(const OptionChains &chains);
	friend std::ostream& operator<<(std::ostream &stream, const OptionChains &chains)
	{
		stream << "ExpirationDate: " << OptionChainPathGenerator::DateToString(chains._Generator.ExpirationDate(),'//') << '\n';
		for (auto &chain_pair : chains._Files)
		{
			stream << "Ticker: " << chain_pair.first << '\n';
			stream << *((OptionChain*)chain_pair.second) << '\n';
		}
		return stream;
	}
};

#endif
