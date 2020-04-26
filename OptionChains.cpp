#include "OptionChains.hpp"

// Constructors/Destructor:
OptionChains::OptionChains(const std::string &containerFolder) : FileTypeContainer(), _Generator(containerFolder)
{

}
OptionChains::OptionChains(const QuantLib::Date &expDate, const QuantLib::Date &valueDate, const std::string &containerFolder) :
	_Generator(expDate,valueDate,containerFolder), FileTypeContainer()
{
	this->ParseFiles(this->_Generator.ValueDate());
}
OptionChains::OptionChains(const OptionChainPathGenerator &gen) : 
	_Generator(gen), FileTypeContainer()
{
	this->ParseFiles(this->_Generator.ValueDate());
}
OptionChains::OptionChains(const OptionChains &chain) : FileTypeContainer(chain), _Generator(chain._Generator)
{

}
OptionChains::~OptionChains()
{

}
// Accessors:
const std::unordered_map<std::string, FileType*>& OptionChains::GetOptionChains() const
{
	return FileTypeContainer::_Files;
}
bool OptionChains::HasOptionChain(const std::string &ticker) const
{
	return FileTypeContainer::_Files.find(ticker) == FileTypeContainer::_Files.end();
}
const FileType* const OptionChains::GetOptionChain(const std::string &ticker) const
{
	if (this->HasOptionChain(ticker))
	{
		throw std::exception("Could not find option chain with ticker.");
	}
	return FileTypeContainer::_Files.find(ticker)->second;
}
// Mutators:
void OptionChains::ParseFiles(const std::vector<std::string> &tickers)
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
			FileTypeContainer::_Files.emplace(ticker, new OptionChain(path));
		}
	}
}
void OptionChains::ParseFiles(const QuantLib::Date &valueDate)
{
	// Pull all option chains in value date folder for given
	// expiration date:
	this->_Generator.ValueDate(valueDate);
	auto valueDateFolder = this->_Generator.ValueDateFolder();
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
			// Pull in all option chains from the folder:
			for (const auto &file : std::filesystem::directory_iterator(entry.path().string()))
			{
				auto ticker = OptionChainPathGenerator::ExtractTicker(file.path().string());
				FileTypeContainer::_Files.emplace(ticker, new OptionChain(file.path().string()));
			}
		}
	}
}
// Overloaded Operators:
OptionChains& OptionChains::operator=(const OptionChains &chains)
{
	if (this != &chains)
	{
		this->_Generator = chains._Generator;
		FileTypeContainer::operator=(chains);
	}
	return *this;
}