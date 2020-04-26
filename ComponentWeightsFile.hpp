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
	static std::string _Headers;
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
		AllComponentsAvailable(OptionChainPathGenerator &gen, const std::string& indexSymbol) const;
	// Overloaded Operators:
	ComponentWeightsFile& operator=(const ComponentWeightsFile&); 
	friend std::ostream& operator<<(std::ostream &stream, const ComponentWeightsFile &file)
	{
		stream << ComponentWeightsFile::_Headers << '\n';
		for (auto &entry : file._Tickers)
		{
			stream << entry.second << '\n';
		}
		return stream;
	}
};

#endif
