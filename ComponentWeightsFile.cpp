#include "ComponentWeightsFile.hpp"

std::string ComponentWeightsFile::_Headers = "Symbol,Weights,DividendRate";

// Constructors/Destructor:
ComponentWeightsFile::ComponentWeightsFile(const std::string& indexSymbol) : _IndexSymbol(indexSymbol), _Tickers()
{
	this->_Tickers.emplace(this->_IndexSymbol, ComponentWeightsFileRow(indexSymbol,1,std::log(1.0185)));
}
ComponentWeightsFile::ComponentWeightsFile(const std::string& indexSymbol, const std::string &path) : _IndexSymbol(indexSymbol), _Tickers()
{
	this->_Tickers.emplace(this->_IndexSymbol, ComponentWeightsFileRow(indexSymbol, 1, std::log(1.0185)));
	this->ParseFile(path);
}
ComponentWeightsFile::ComponentWeightsFile(const ComponentWeightsFile &file) : _IndexSymbol(file._IndexSymbol), _Tickers(file._Tickers)
{

}
ComponentWeightsFile::~ComponentWeightsFile()
{

}
// Accessors:
const std::string& ComponentWeightsFile::IndexSymbol() const
{
	return this->_IndexSymbol;
}
const std::unordered_map<std::string, ComponentWeightsFileRow>& ComponentWeightsFile::Tickers() const
{
	return this->_Tickers;
}
// Interface Methods:
void ComponentWeightsFile::ParseFile(const std::string &path)
{
	if (!this->PathExists(path))
	{
		throw std::exception("path does not exist.");
	}
	std::fstream file(path);
	if (!file)
	{
		throw std::exception("Could not open file at path.");
	}
	std::string line;
	std::getline(file, line);
	while (!file.eof())
	{
		std::getline(file, line);
		auto row = ComponentWeightsFileRow(line);
		this->_Tickers.emplace(std::string(row.Ticker()), row);
	}
	file.close();
}

std::pair<OptionChainPathGenerator, std::set<std::string>> ComponentWeightsFile::AllComponentsAvailable(const OptionChainPathGenerator &gen, 
	QuantLib::Date *afterDate) const
{
	// Search for expiration date folder(s) where all components have options trading
	// or the greatest number of options trading:
	std::pair<OptionChainPathGenerator, std::set<std::string>> output;
	auto vdFolder = gen.ValueDateFolder();
	OptionChainPathGenerator outGen(gen);
	for (const auto &expDateFolder : std::filesystem::directory_iterator(vdFolder))
	{
		std::string folder(expDateFolder.path().string());
		if (afterDate != nullptr && OptionChainPathGenerator::ExtractExpirationDate_Folder(folder) < *afterDate)
		{
			continue;
		}
		std::set<std::string> curr_tickers;
		// Pull in all option chains from the folder:
		for (const auto &file : std::filesystem::directory_iterator(folder))
		{
			auto ticker = OptionChainPathGenerator::ExtractTicker(file.path().string());
			if (this->_Tickers.find(ticker) != this->_Tickers.end())
			{
				curr_tickers.emplace(ticker);
			}
		}
		if (curr_tickers.find(this->_IndexSymbol) != curr_tickers.end() && curr_tickers.size() > output.second.size())
		{
			auto expDate = OptionChainPathGenerator::ExtractExpirationDate_Folder(expDateFolder.path().string());
			outGen.ExpirationDate(expDate);
			output = std::pair<OptionChainPathGenerator, std::set<std::string>>(outGen, curr_tickers);
		}
	}
	return output;
}
// Overloaded Operators:
ComponentWeightsFile& ComponentWeightsFile::operator=(const ComponentWeightsFile &file)
{
	if (this != &file)
	{
		this->_IndexSymbol = file._IndexSymbol;
		this->_Tickers = file._Tickers;
	}
	return *this;
}
