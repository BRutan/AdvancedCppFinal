#include "TickersFile.hpp"


// Constructors/Destructor:
TickersFile::TickersFile(const std::string &path) : _Tickers()
{
	this->ParseFile(path);
}
TickersFile::TickersFile(const TickersFile &file) : _Tickers(file._Tickers)
{

}
TickersFile::~TickersFile()
{

}
// Accessors:
const std::unordered_map<std::string, TickersFileRow>& TickersFile::Tickers() const
{
	return this->_Tickers;
}
// Interface Methods:
void TickersFile::ParseFile(const std::string &path)
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
		auto row = TickersFileRow(line);
		this->_Tickers.emplace(row.Ticker(), row);
	}
	file.close();
}
// Overloaded Operators:
TickersFile& TickersFile::operator=(const TickersFile &file)
{
	if (this != &file)
	{
		this->_Tickers = file._Tickers;
	}
	return *this;
}
