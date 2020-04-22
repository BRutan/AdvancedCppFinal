#include "OptionChain.hpp"

// Private Helpers:
void OptionChain::_ExtractAttributes(const std::string &path)
{
	auto index = path.rfind('\\');
	std::string fileName((index != path.npos) ? path.substr(index + 1) : path);
	auto firstIDX = fileName.find_first_of('_');
	this->_Ticker = fileName.substr(0, firstIDX);
	this->_ValMonth = std::stoul(fileName.substr(firstIDX + 1, 2));
	this->_ValDay = std::stoul(fileName.substr(firstIDX + 4, 2));
	this->_ValYear = std::stoul(fileName.substr(firstIDX + 7, 4));
	this->_ExpMonth = std::stoul(fileName.substr(firstIDX + 12, 2));
	this->_ExpDay = std::stoul(fileName.substr(firstIDX + 15, 2));
	this->_ExpYear = std::stoul(fileName.substr(firstIDX + 18, 4));
}
// Constructors/Destructor:
OptionChain::OptionChain(const std::string &path) : FileType(), _ExpYear(), _ExpMonth(), _ExpDay(),
	_ValYear(), _ValMonth(), _ValDay(), _Ticker()
{
	this->ParseFile(path);
	this->_ExtractAttributes(path);
}
OptionChain::OptionChain(const OptionChain &chain) : FileType(chain._Data), _ExpYear(chain._ExpYear), _ExpMonth(chain._ExpMonth), 
_ExpDay(chain._ExpDay), _ValYear(chain._ValYear), _ValMonth(chain._ValMonth), _ValDay(chain._ValDay), _Ticker(chain._Ticker)
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
	std::ifstream file(filepath);
	if (!file)
	{
		throw std::exception("Could not open file.");
	}
	std::string row;
	std::getline(file, row);
	while (!file.eof())
	{
		std::getline(file, row);
		auto newRow = new OptionChainRow(row);
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
std::string OptionChain::ValueDateStr() const
{
	std::ostringstream out;
	out << ((this->_ValMonth < 10) ? "0" : "") << this->_ValMonth << "//" <<
		((this->_ValDay < 10) ? "0" : "") << this->_ValDay << "//" << this->_ValYear;
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


std::string OptionChain::_HeaderString = "Strike,LastPrice,Bid,Ask,Change,PercentChange,Volume,OpenInterest,ImpliedVol";
