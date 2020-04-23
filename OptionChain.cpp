#include "OptionChain.hpp"

std::string OptionChain::_HeaderString = "Strike,LastPrice,Bid,Ask,Change,PercentChange,Volume,OpenInterest,ImpliedVol";

// Private Helpers:
void OptionChain::_ExtractAttributes(const std::string &path)
{	
	auto index = path.rfind('\\');
	std::string fileName((index != path.npos) ? path.substr(index + 1) : path);
	auto firstIDX = fileName.find_first_of('_');
	FileType::_ExtractAttributes(firstIDX, fileName);
	this->_Ticker = fileName.substr(0, firstIDX);
	this->_ExpMonth = std::stoul(fileName.substr(firstIDX + 12, 2));
	this->_ExpDay = std::stoul(fileName.substr(firstIDX + 15, 2));
	this->_ExpYear = std::stoul(fileName.substr(firstIDX + 18, 4));
}
// Constructors/Destructor:
OptionChain::OptionChain(const std::string &path) : FileType(), _ExpYear(), _ExpMonth(), _ExpDay(), _Ticker()
{
	this->ParseFile(path);
}
OptionChain::OptionChain(const OptionChain &chain) : FileType(&chain), _ExpYear(chain._ExpYear), _ExpMonth(chain._ExpMonth), 
_ExpDay(chain._ExpDay),  _Ticker(chain._Ticker)
{
	
}
OptionChain::~OptionChain()
{

}
// Accessors:
unsigned OptionChain::ExpYear() const
{
	return this->_ExpYear;
}
unsigned OptionChain::ExpDay() const
{
	return this->_ExpDay;
}
unsigned OptionChain::ExpMonth() const
{
	return this->_ExpMonth;
}
const std::string& OptionChain::Ticker() const
{
	return this->_Ticker;
}
// Mutators:
void OptionChain::ParseFile(const std::string & filepath)
{
	if (this->_Data.size())
	{
		this->_Data.clear();
		this->_IsCalls = false;
	}
	if (filepath.substr(filepath.length() - 10, 10) == "_Calls.csv")
	{
		this->_IsCalls = true;
	}
	this->_ExtractAttributes(filepath);
	std::ifstream file(filepath);
	if (!file)
	{
		throw std::exception("Could not open file.");
	}
	// Calculate the option tenor in years:
	double tenor = (this->_ExpYear - this->_ValYear);
	if (this->_ExpMonth != this->_ValMonth)
	{
		//tenor += std::max(this->_ExpMonth - this->_ValMonth, 0) / 365.0;
	}
	std::string row;
	std::getline(file, row);
	while (!file.eof())
	{
		std::getline(file, row);
		auto newRow = new OptionChainRow(row, tenor);
		this->_Data.emplace(newRow->Strike(), newRow);
	}
	file.close();
}
// Interface Methods:
std::string OptionChain::ExpDateStr() const
{
	std::ostringstream out;
	out << ((this->_ExpMonth < 10) ? "0" : "") << this->_ExpMonth << "//" <<
		((this->_ExpDay < 10) ? "0" : "") << this->_ExpDay << "//" << this->_ExpYear;
	return out.str();
}
// Overloaded Operators:
OptionChain& OptionChain::operator=(const OptionChain &chain)
{
	if (this != &chain)
	{
		this->_ExpDay = chain._ExpDay;
		this->_ExpMonth = chain._ExpMonth;
		this->_ExpYear = chain._ExpYear;
		this->_IsCalls = chain._IsCalls;
		this->_Ticker = chain._Ticker;
		FileType::operator=(chain);
	}
	return *this;
}
