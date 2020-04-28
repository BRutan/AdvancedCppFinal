#include "PNLFileRow.hpp"

PNLFileRow::PNLFileRow() : _Ticker(), _ChgPercent(0),
	_ChgPrice(0), _ImpliedCorrel(0), _ValueDate(), _Price(0), _Delta(0), _Gamma(0), _Vega(0), _Rho(0), _Theta(0)
{

}
PNLFileRow::PNLFileRow(const std::string &row) : _Ticker(), _ChgPercent(0),
	_ChgPrice(0), _ImpliedCorrel(0), _ValueDate(), _Price(0), _Delta(0), _Gamma(0), _Vega(0), _Rho(0), _Theta(0)
{
	this->ParseRow(row);
}
PNLFileRow::PNLFileRow(const PNLFileRow& row) : _Ticker(row._Ticker), _ChgPercent(row._ChgPercent),
	_ChgPrice(row._ChgPrice), _ImpliedCorrel(row._ImpliedCorrel), _ValueDate(row._ValueDate), _Price(row._Price),
	_Delta(row._Delta), _Gamma(row._Gamma), _Vega(row._Vega), _Rho(row._Rho), _Theta(row._Theta)
{

}
PNLFileRow::~PNLFileRow()
{

}
// Accessors:
double PNLFileRow::Price() const
{
	return this->_Price;
}
const QuantLib::Date& PNLFileRow::ValueDate() const
{
	return this->_ValueDate;
}
double PNLFileRow::Delta() const
{
	return this->_Delta;
}
double PNLFileRow::Gamma() const
{
	return this->_Gamma;
}
double PNLFileRow::Rho() const
{
	return this->_Rho;
}
double PNLFileRow::Vega() const
{
	return this->_Vega;
}
double PNLFileRow::Theta() const
{
	return this->_Theta;
}
double PNLFileRow::ImpliedCorrelation() const
{
	return this->_ImpliedCorrel;
}
double PNLFileRow::PriceChg() const
{
	return this->_ChgPrice;
}
double PNLFileRow::PercentChg() const
{
	return this->_ChgPercent;
}
const std::string& PNLFileRow::Ticker() const
{
	return this->_Ticker;
}
// Mutators:
void PNLFileRow::Delta(double delta)
{
	this->_Delta = delta;
}
void PNLFileRow::Gamma(double gamma)
{
	this->_Gamma = gamma;
}
void PNLFileRow::Rho(double rho)
{
	this->_Rho = rho;
}
void PNLFileRow::Vega(double vega)
{
	this->_Vega = vega;
}
void PNLFileRow::Theta(double theta)
{
	this->_Theta = theta;
}
void PNLFileRow::ParseRow(const std::string &row)
{
	std::istringstream str(row);
	std::string cell;
	std::size_t index = 0;
	double val;
	while (index < 5 && std::getline(str, cell, ','))
	{
		std::istringstream parse(cell);
		switch (index)
		{
		case 0:
			this->_ValueDate = FileType::StringToDate(cell, '//');
			break;
		case 1:
			this->_Ticker = cell;
			break;
		case 2:
			this->_ChgPrice = ((parse >> val) ? val : 0);
			break;
		case 3:
			this->_ChgPercent = ((parse >> val) ? val : 0);
			break;
		case 4:
			this->_ImpliedCorrel = ((parse >> val) ? val : 0);
			break;
		}
		++index;
	}
}
void PNLFileRow::Price(double pc)
{
	this->_Price = pc;
}
void PNLFileRow::ImpliedCorrelation(double corr)
{
	this->_ImpliedCorrel = corr;
}
void PNLFileRow::PriceChg(double chg)
{
	this->_ChgPrice = chg;
}
void PNLFileRow::PercentChg(double chg)
{
	this->_ChgPercent = chg;
}
void PNLFileRow::ValueDate(const QuantLib::Date& dt)
{
	this->_ValueDate = dt;
}
void PNLFileRow::Ticker(const std::string &ticker)
{
	this->_Ticker = ticker;
}
// Overloaded Operators:
PNLFileRow& PNLFileRow::operator=(const PNLFileRow &row)
{
	if (this != &row)
	{
		this->_Price = row._Price;
		this->_ChgPercent = row._ChgPercent;
		this->_ChgPrice = row._ChgPrice;
		this->_ImpliedCorrel = row._ImpliedCorrel;
		this->_Ticker = row._Ticker;
		this->_ValueDate = row._ValueDate;
		this->_Delta = row._Delta;
		this->_Gamma = row._Gamma;
		this->_Rho = row._Rho;
		this->_Theta = row._Theta;
		this->_Vega = row._Vega;
	}
	return *this;
}
