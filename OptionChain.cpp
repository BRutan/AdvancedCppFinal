#include "OptionChain.hpp"


// Constructors/Destructor:
OptionChain::OptionChain(const std::string &filePath)
{
	this->ParseFile(filePath);
}
OptionChain::~OptionChain()
{

}
// Accessors:
const std::string& OptionChain::Ticker() const
{
	return this->_Ticker;
}
const std::unordered_map<float, OptionChainRow>& OptionChain::Rows() const
{
	return this->_Rows;
}
// Mutators:
void OptionChain::ParseFile(const std::string & filepath)
{
	if (this->_Rows.count)
	{
		this->_Rows = std::unordered_map<float, OptionChainRow>();
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
	while (!file.eof())
	{
		std::getline(file, row);
		auto newRow = OptionChainRow(row);
		this->_Rows[newRow.Strike()] = newRow;
	}
}
// Interface Methods:
std::string OptionChain::ExpDateStr() const
{
	std::ostringstream out;
	out << this->_ExpYear << this->_ExpMonth << this->_ExpDay;
	return out.str();
}