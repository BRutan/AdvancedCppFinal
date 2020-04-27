#include "OptionChains.hpp"

// Constructors/Destructor:
OptionChains::OptionChains(const std::string &containerFolder) : FileTypeContainer(), _Generator(containerFolder)
{

}
OptionChains::OptionChains(const QuantLib::Date &expDate, const QuantLib::Date &valueDate, const std::string &containerFolder) :
	_Generator(expDate,valueDate,containerFolder), FileTypeContainer()
{
	this->ParseFiles(expDate);
}
OptionChains::OptionChains(const OptionChainPathGenerator &gen) : 
	_Generator(gen), FileTypeContainer()
{
	this->ParseFiles(gen.ExpirationDate());
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
const OptionChain* const OptionChains::GetOptionChain(const std::string &ticker) const
{
	if (this->HasOptionChain(ticker))
	{
		throw std::exception("Could not find option chain with ticker.");
	}
	return dynamic_cast<OptionChain*>(FileTypeContainer::_Files.find(ticker)->second);
}
// Mutators:
void OptionChains::ParseFiles(const std::vector<std::string> &tickers, const QuantLib::Date &expDate)
{
	// Parse all ticker files for value date and expiration for given tickers:
	this->_Generator.ExpirationDate(expDate);
	if (!this->PathExists(this->_Generator.ValueDateFolder()))
	{
		throw std::exception("value date folder does not exist");
	}
	this->_Generator.ExpirationDate(expDate);
	if (!this->PathExists(this->_Generator.ExpirationDateFolder()))
	{
		throw std::exception("expiration date folder does not exist.");
	}
	for (auto &ticker : tickers)
	{
		auto tickerPath = this->_Generator.TickerPath(ticker);
		if (this->_Generator.PathExists(ticker))
		{
			auto path = this->_Generator.TickerPath(ticker);
			FileTypeContainer::_Files.emplace(ticker, new OptionChain(path));
		}
	}
}
void OptionChains::ParseFiles(const QuantLib::Date &expDate)
{
	// Pull all option chains in value date folder for given
	// expiration date:
	auto valueDateFolder = this->_Generator.ValueDateFolder();
	if (!this->PathExists(valueDateFolder))
	{
		throw std::exception("value date folder does not exist");
	}
	this->_Generator.ExpirationDate(expDate);
	auto expFolder = this->_Generator.ExpirationDateFolder();
	if (!this->PathExists(expFolder))
	{
		throw std::exception("expiration date folder does not exist.");
	}
	// Parse all option chains in the folder for expiration date:
	for (const auto &file: std::filesystem::directory_iterator(expFolder))
	{
		// Pull in all option chains from the folder:
		auto ticker = OptionChainPathGenerator::ExtractTicker(file.path().string());
		FileTypeContainer::_Files.emplace(ticker, new OptionChain(file.path().string()));
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