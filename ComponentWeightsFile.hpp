#ifndef TICKERSFILE_HPP
#define TICKERSFILE_HPP

#include <fstream>
#include <set>
#include <string>
#include "FileType.hpp"
#include "ComponentWeightsFileRow.hpp"

class ComponentWeightsFile : public FileType
{
private:
	// All unique tickers in file:
	std::unordered_map<std::string, ComponentWeightsFileRow> _Tickers;
public:
	// Constructors/Destructor:
	ComponentWeightsFile(const std::string &path);
	ComponentWeightsFile(const ComponentWeightsFile&);
	virtual ~ComponentWeightsFile();
	// Accessors:
	const std::unordered_map<std::string, ComponentWeightsFileRow>& Tickers() const;
	// Interface Methods:
	void ParseFile(const std::string &path);
	// Overloaded Operators:
	ComponentWeightsFile& operator=(const ComponentWeightsFile&); 
};

#endif
