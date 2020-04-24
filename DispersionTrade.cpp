#include "DispersionTrade.hpp"

///////////////////////
// DispersionTradeAttributes definitions:


// Constructors/Destructor:
DispersionTradeAttributes::DispersionTradeAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), SecurityAttributes(isLong)
{
	// Ensure that long/short attributes are set correctly:
	if (isLong)
	{
		
	}

}
DispersionTradeAttributes::DispersionTradeAttributes(const DispersionTradeAttributes &attr) : _IndexName(attr._IndexName),
	_IndexOption(attr._IndexOption), _ConstituentOptions(attr._ConstituentOptions), SecurityAttributes(attr.IsLong())
{

}
DispersionTradeAttributes::~DispersionTradeAttributes()
{

}
// Accessors:
const std::string& DispersionTradeAttributes::IndexName() const
{
	return this->_IndexName;
}
const Option& DispersionTradeAttributes::IndexOption() const
{
	return this->_IndexOption;
}
const std::unordered_map<std::string, std::pair<Option, double>>& DispersionTradeAttributes::ConstituentOptions() const
{
	return this->_ConstituentOptions;
}
// Overloaded Operators:
DispersionTradeAttributes& DispersionTradeAttributes::operator=(const DispersionTradeAttributes &attr)
{
	if (this != &attr)
	{
		this->_ConstituentOptions = attr._ConstituentOptions;
		this->_IndexName = attr._IndexName;
		this->_IndexOption = attr._IndexOption;
		SecurityAttributes::operator=(attr);
	}
	return *this;
}

// Constructors/Destructor:
DispersionTrade::DispersionTrade(const DispersionTradeAttributes &attr) : Trade(&attr)
{

}
DispersionTrade::DispersionTrade(const DispersionTrade& trade) : Trade(trade.Attributes())
{

}
DispersionTrade::~DispersionTrade()
{

}
// Accessors:
const std::string& DispersionTrade::IndexName() const
{
	return dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get())->IndexName();
}
const Option& DispersionTrade::IndexOption() const
{
	return dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get())->IndexOption();
}
const std::unordered_map<std::string, std::pair<Option, double>>& DispersionTrade::ConstitutentOptions() const
{
	return dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get())->ConstituentOptions();
}
// Interface Methods:
std::pair<DispersionTrade, double> DispersionTrade::OptimalDispersionTrade(const std::string &valueDateFolder, unsigned expMonth, 
	unsigned expDay, unsigned expYear, const DispersionTradeAttributes &attrs)
{
	OptionChains allchains(valueDateFolder, expMonth, expDay, expYear);
	auto indexChain = allchains.GetOptionChain(attrs.IndexName());
	auto chains = allchains.GetOptionChains();
	bool isNegative = false;
	double maxAbsImpCorr = 0, currAbsImpCorr = 0;
	for (auto &row : indexChain->Data())
	{
		auto converted = dynamic_cast<OptionChainRow*>(row.second);
		
		currAbsImpCorr = 0;
		for (auto &constituentChain : attrs.ConstituentOptions())
		{
			currAbsImpCorr += 0;
		}
	}
	// Generate trade using optimal strikes:

}
double DispersionTrade::Delta() const
{
	double delta = 0;
	auto attr = dynamic_cast<OptionAttributes*>(this->Attributes().get());

}
double DispersionTrade::ImpliedCorrelation() const
{
	 std::size_t index = 0;
	double numerator = 0, denominator = 0;
	double curr_risk_entry = 0, sub_risk_entry = 0, iv = 0;
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	for (auto &entry : attr->ConstituentOptions())
	{
		iv = dynamic_cast<OptionAttributes*>(entry.second.first.Attributes().get())->ImpliedVol();
		curr_risk_entry = entry.second.second * iv;
		numerator += curr_risk_entry * curr_risk_entry;
		std::size_t sub_index = 0;
		for (auto &sub_entry : attr->ConstituentOptions())
		{
			if (sub_index > index)
			{
				iv = dynamic_cast<OptionAttributes*>(sub_entry.second.first.Attributes().get())->ImpliedVol();
				sub_risk_entry = sub_entry.second.second * iv;
				denominator += curr_risk_entry * sub_risk_entry;
			}
			++sub_index;
		}
		++index;
	}
	double indexCorr = dynamic_cast<OptionAttributes*>(attr->IndexOption().Attributes().get())->ImpliedVol();
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
		Trade::operator=(trade);
	}
	return *this;
}