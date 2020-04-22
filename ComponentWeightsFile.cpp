#include "ComponentWeightsFile.hpp"


// Constructors/Destructor:
ComponentWeightsFile::ComponentWeightsFile(const std::string &path) : _Tickers()
{
	this->ParseFile(path);
}
ComponentWeightsFile::ComponentWeightsFile(const ComponentWeightsFile &file) : _Tickers(file._Tickers)
{

}
ComponentWeightsFile::~ComponentWeightsFile()
{

}
// Accessors:
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
		this->_Tickers.emplace(row.Ticker(), row);
	}
	file.close();
}
// Overloaded Operators:
ComponentWeightsFile& ComponentWeightsFile::operator=(const ComponentWeightsFile &file)
{
	if (this != &file)
	{
		this->_Tickers = file._Tickers;
	}
	return *this;
}
