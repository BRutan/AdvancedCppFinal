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
	double _AverageIV;
	bool _IsCalls;
	void _ExtractAttributes(const std::string &path);
	static std::string _HeaderString;
	std::vector<double> _SortedStrikes;
	// Private Methods:
	void _SortStrikes();
public:
	// Constructors/Destructor:
	OptionChain();
	OptionChain(const std::string &path);
	explicit OptionChain(const OptionChain &chain);
	virtual ~OptionChain();
	// Accessors:
	double AverageImpliedVolatility() const;
	const QuantLib::Date& ExpirationDate() const;
	double GetClosestStrike(double strike) const;
	bool HasRow(double strike) const;
	const OptionChainRow * GetRow(double strike) const;
	bool HasStrike(double strike) const;
	const std::string& Ticker() const;
	const std::vector<double>& Strikes() const;
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
