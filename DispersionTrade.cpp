#include "DispersionTrade.hpp"



	// Constructors/Destructor:
DispersionTrade::DispersionTrade(const std::string& indexName, const Option& indexOption, 
	const std::unordered_map<std::string, std::pair<Option, double>>& constitutentOptions) :
	_IndexName(indexName), _IndexOption(indexOption), _ConstituentOptions(constitutentOptions)
{

}
DispersionTrade::DispersionTrade(const DispersionTrade& trade) : _IndexName(trade._IndexName),
	_IndexOption(trade._IndexOption), _ConstituentOptions(trade._ConstituentOptions)
{

}
DispersionTrade::~DispersionTrade()
{

}
// Accessors:
const std::string& DispersionTrade::IndexName() const
{
	return this->_IndexName;
}
const Option& DispersionTrade::IndexOption() const
{
	return this->_IndexOption;
}
const std::unordered_map<std::string, Option>& DispersionTrade::ConstitutentOptions() const
{
	return this->_ConstitutentOptions;
}
// Interface Methods:
std::pair<DispersionTrade, double> DispersionTrade::OptimalDispersionTrade(const std::string &optionChainsPaths)
{


}
double DispersionTrade::ImpliedCorrelation() const
{
	std::size_t index = 0;
	double numerator = 0;
	double denominator = 0;
	double curr_risk_entry = 0;
	double sub_risk_entry = 0;
	for (auto &entry : this->_ConstituentOptions)
	{
		curr_risk_entry = entry.second.second * ((OptionAttributes*)entry.second.first.Attributes())->ImpliedVol();
		numerator += curr_risk_entry * curr_risk_entry;
		std::size_t sub_index = 0;
		for (auto &sub_entry : this->_ConstituentOptions)
		{
			if (sub_index > index)
			{
				sub_risk_entry = sub_entry.second.second * ((OptionAttributes*)sub_entry.second.first.Attributes())->ImpliedVol();
				denominator += curr_risk_entry * sub_risk_entry;
			}
			++sub_index;
		}
		++index;
	}
	double indexCorr = (OptionAttributes*)(this->_IndexOption.Attributes)->ImpliedVol();
	return (indexCorr - numerator) / denominator;
}
double DispersionTrade::ImpliedCorrelation(const std::string &indexName, const OptionChains &chains)
{
	return 0;
}
DispersionTrade& DispersionTrade::operator=(const DispersionTrade &trade)
{
	if (this != &trade)
	{
		this->_ConstituentOptions = trade._ConstituentOptions;
		this->_IndexName = trade._IndexName;
		this->_IndexOption = trade._IndexOption;
		Trade::operator=(trade);
	}
	return *this;
}