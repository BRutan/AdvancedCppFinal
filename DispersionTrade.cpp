#include "DispersionTrade.hpp"

///////////////////////
// DispersionTradeAttributes definitions:
///////////////////////
// Constructors/Destructor:
DispersionTradeAttributes::DispersionTradeAttributes() : _IndexName(), _IndexOption(), _ConstituentOptions(), SecurityAttributes()
{

}
DispersionTradeAttributes::DispersionTradeAttributes(bool isLong, const std::string& indexName, const Option& indexOption,
	const std::unordered_map<std::string, std::pair<Option, double>> constitutentOptions) : _IndexName(indexName),
	_IndexOption(indexOption), _ConstituentOptions(constitutentOptions), SecurityAttributes(isLong)
{
	// Ensure that long/short attributes are set correctly:
	// (if long index, short constituents, vice versa):
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
// Mutators:
void DispersionTradeAttributes::ConstituentOptions(const std::unordered_map<std::string, std::pair<Option, double>> &constits)
{
	this->_ConstituentOptions = constits;
}
void DispersionTradeAttributes::IndexName(std::string& indexName)
{
	this->_IndexName = indexName;
}
void DispersionTradeAttributes::IndexOption(const Option& indexOpt)
{
	this->_IndexOption = indexOpt;
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

/////////////////////
// DispersionTrade definitions:
/////////////////////
// Constructors/Destructor:
DispersionTrade::DispersionTrade(const DispersionTradeAttributes &attr) : Trade(std::make_shared<DispersionTradeAttributes>(attr))
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
std::pair<DispersionTrade, double> DispersionTrade::OptimalDispersionTrade(const std::string &valueDateFolder, 
	const OptionChainPathGenerator &gen, const DispersionTradeAttributes &attrs)
{
	OptionChains allchains(valueDateFolder, gen);
	auto indexChain = allchains.GetOptionChain(attrs.IndexName());
	auto chains = allchains.GetOptionChains();
	bool isNegative = false;
	double maxAbsImpCorr = 0, currImpCorr = 0;
	for (auto &row : indexChain->Data())
	{
		auto converted = dynamic_cast<OptionChainRow*>(row.second);		
		currImpCorr = 0;
		for (auto &constituentChain : attrs.ConstituentOptions())
		{
			currImpCorr += 0;
		}
		if (std::abs(currImpCorr) > maxAbsImpCorr)
		{
			maxAbsImpCorr = std::abs(currImpCorr);
			// Strategy goes long the index option, short the components if the 
			// 
			bool isLong = currImpCorr < 0;
		}
	}
	// Generate trade using optimal strikes:
	DispersionTrade trade(attrs);
	return std::make_pair(trade, maxAbsImpCorr);
}
double DispersionTrade::Delta() const
{
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double delta = attr->IndexOption().Delta();
	for (auto &constituent : attr->ConstituentOptions())
	{
		delta += constituent.second.first.Delta() * constituent.second.second;
	}
	return delta;
}
double DispersionTrade::Gamma() const
{
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double gamma = attr->IndexOption().Gamma();
	for (auto &constituent : attr->ConstituentOptions())
	{
		gamma += constituent.second.first.Gamma() * constituent.second.second;
	}
	return gamma;
}
double DispersionTrade::Theta() const
{
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double theta = attr->IndexOption().Gamma();
	for (auto &constituent : attr->ConstituentOptions())
	{
		theta += constituent.second.first.Theta() * constituent.second.second;
	}
	return theta;
}
double DispersionTrade::Vega() const
{
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double vega = attr->IndexOption().Vega();
	for (auto &constituent : attr->ConstituentOptions())
	{
		vega += constituent.second.first.Vega() * constituent.second.second;
	}
	return vega;
}
double DispersionTrade::Rho() const
{
	auto attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double rho = attr->IndexOption().Rho();
	for (auto &constituent : attr->ConstituentOptions())
	{
		rho += constituent.second.first.Rho() * constituent.second.second;
	}
	return rho;
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
double DispersionTrade::CalculatePNL(const std::shared_ptr<SecurityAttributes> &attr)
{
	auto new_attr = dynamic_cast<const DispersionTradeAttributes*>(attr.get());
	auto this_attr = dynamic_cast<DispersionTradeAttributes*>(this->Attributes().get());
	double index_price_diff = this_attr->IndexOption().Price() - new_attr->IndexOption().Price();
	double constituent_price_diff = 0;
	for (auto &constituent : this_attr->ConstituentOptions())
	{
		auto match = new_attr->ConstituentOptions().find(constituent.first);
		constituent_price_diff += (constituent.second.first.Price() - match->second.first.Price()) * constituent.second.second;
	}
	return index_price_diff + constituent_price_diff;
}
DispersionTrade& DispersionTrade::operator=(const DispersionTrade &trade)
{
	if (this != &trade)
	{
		Trade::operator=(trade);
	}
	return *this;
}