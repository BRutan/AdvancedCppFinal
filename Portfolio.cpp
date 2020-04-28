#include "Portfolio.hpp"


PortfolioAttributes::PortfolioAttributes()
{

}
PortfolioAttributes::PortfolioAttributes(const PortfolioAttributes& attr)
{

}
PortfolioAttributes::~PortfolioAttributes()
{

}
// Overloaded Operators:
PortfolioAttributes& PortfolioAttributes::operator=(const PortfolioAttributes& attr)
{
	return *this;
}

// Constructors/Destructor:
Portfolio::Portfolio() : _Securities()
{
	
}
Portfolio::Portfolio(const Portfolio &port) : _Securities(port._Securities)
{

}
// Accessors:
const std::unordered_map<std::string, std::shared_ptr<Security>>& Portfolio::Securities() const
{
	return this->_Securities;
}
// Interface Methods:
double Portfolio::Price() const
{
	double price = 0;
	for (auto &entry : this->_Securities)
	{
		price += entry.second->Price();
	}
	return price;
}
double Portfolio::CalculatePNL(const Portfolio &port) const
{
	double pnl = 0;
	for (auto &entry : this->_Securities)
	{
		auto match = port._Securities.find(entry.first);
		if (match != port._Securities.end())
		{
			pnl += match->second->Price() - entry.second->Price();
		}
	}
	return pnl;
}
double Portfolio::Delta() const
{
	double delta = 0;
	for (auto &entry : this->_Securities)
	{
		delta += entry.second->Delta();
	}
	return delta;
}
double Portfolio::Gamma() const
{
	double gamma = 0;
	for (auto &entry : this->_Securities)
	{
		gamma += entry.second->Delta();
	}
	return gamma;
}
double Portfolio::Theta() const
{
	double theta = 0;
	for (auto &entry : this->_Securities)
	{
		theta += entry.second->Delta();
	}
	return theta;
}
double Portfolio::Vega() const
{
	double vega = 0;
	for (auto &entry : this->_Securities)
	{
		vega += entry.second->Delta();
	}
	return vega;
}
double Portfolio::Rho() const
{
	double rho = 0;
	for (auto &entry : this->_Securities)
	{
		rho += entry.second->Rho();
	}
	return rho;
}
Portfolio Portfolio::CreateCopy() const
{
	return Portfolio(*this);
}
// Overloaded Operators:
Portfolio& Portfolio::operator=(const Portfolio &port)
{
	if (this != &port)
	{
		this->_Securities = port._Securities;
		Portfolio::Derivative::operator=(port);
	}
	return *this;
}
PNLFileRow Portfolio::operator-(const Portfolio &port)
{
	return PNLFileRow();
}