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
	auto month = std::stoul(fileName.substr(firstIDX + 12, 2));
	auto day = std::stoul(fileName.substr(firstIDX + 15, 2));
	auto year = std::stoul(fileName.substr(firstIDX + 18, 4));
	this->_ExpDate = QuantLib::Date(day, FileType::MonthToEnum(month), year);
}
// Constructors/Destructor:
OptionChain::OptionChain() : FileType(), _ExpDate(), _Ticker()
{

}
OptionChain::OptionChain(const std::string &path) : FileType(), _ExpDate(), _Ticker()
{
	this->ParseFile(path);
}
OptionChain::OptionChain(const OptionChain &chain) : FileType(&chain), _ExpDate(chain._ExpDate), _Ticker(chain._Ticker)
{
	
}
OptionChain::~OptionChain()
{

}
// Accessors:
const QuantLib::Date& OptionChain::ExpirationDate() const
{
	return this->_ExpDate;
}
double OptionChain::GetClosestStrike(double strike) const
{
	// Sort by strike:
	std::vector<double> sorted_strikes(this->_Data.size());
	for (auto &iter : this->_Data)
	{
		sorted_strikes.push_back(iter.first);
	}
	std::sort(sorted_strikes.begin(), sorted_strikes.end());
	// Find closest option chain:
	for (auto iter = sorted_strikes.begin(); iter != sorted_strikes.end(); ++iter)
	{
		if (strike < *iter)
		{
			return *iter;
		}
		else if (strike < *(iter + 1))
		{
			return ((std::abs(*iter - strike) > std::abs(*(iter + 1) - strike)) ? *(iter + 1) : *iter);
		}
	}
}
const OptionChainRow& OptionChain::GetRow(double strike) const
{
	auto match = this->_Data.find(strike);
	if (match == this->_Data.end())
	{
		std::exception("Strike not in data set.");
	}
	return *dynamic_cast<OptionChainRow*>(match->second);
}
bool OptionChain::HasStrike(double strike) const
{
	return this->_Data.find(strike) != this->_Data.end();
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
	double tenor = (QuantLib::Actual365Fixed().yearFraction(this->_ValueDate, this->_ExpDate));
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
	return FileType::DateToString(this->_ExpDate, '//');
}
// Overloaded Operators:
OptionChain& OptionChain::operator=(const OptionChain &chain)
{
	if (this != &chain)
	{
		this->_ExpDate = chain._ExpDate;
		this->_IsCalls = chain._IsCalls;
		this->_Ticker = chain._Ticker;
		FileType::operator=(chain);
	}
	return *this;
}
