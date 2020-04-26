#ifndef TICKERSFILE_HPP
#define TICKERSFILE_HPP

#include <fstream>
#include <ql/time/date.hpp>
#include <set>
#include <string>
#include <set>
#include "ComponentWeightsFileRow.hpp"
#include "FileType.hpp"
#include "OptionChainPathGenerator.hpp"

class ComponentWeightsFile : public FileType
{
private:
	// All unique tickers in file:
	std::unordered_map<std::string, ComponentWeightsFileRow> _Tickers;
public:
	// Constructors/Destructor:
	ComponentWeightsFile();
	ComponentWeightsFile(const std::string &path);
	ComponentWeightsFile(const ComponentWeightsFile&);
	virtual ~ComponentWeightsFile();
	// Accessors:
	const std::unordered_map<std::string, ComponentWeightsFileRow>& Tickers() const;
	// Interface Methods:
	virtual void ParseFile(const std::string &path);
	std::pair<OptionChainPathGenerator, std::set<std::string>>
		AllComponentsAvailable(const OptionChainPathGenerator &gen, const std::string& indexSymbol) const;
	// Overloaded Operators:
	ComponentWeightsFile& operator=(const ComponentWeightsFile&); 
};

#endif
