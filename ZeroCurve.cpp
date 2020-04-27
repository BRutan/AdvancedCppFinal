#include "ZeroCurve.hpp"

std::string ZeroCurve::_Header = "Tenor,Yield";
// Private Helpers:
void ZeroCurve::_SetInterp(const InterpolationType &interp)
{
	std::vector<double> tenors;
	std::vector<double> rates;
	tenors.reserve(this->_ZeroRates.size());
	rates.reserve(this->_ZeroRates.size());
	for (auto &elem : this->_ZeroRates)
	{
		tenors.push_back(elem.first);
	}
	// Sort the tenors for the interpolator:
	std::sort(tenors.begin(), tenors.end());
	for (auto &elem : tenors)
	{
		rates.push_back(this->_ZeroRates[elem]);
	}
	switch (interp)
	{
	case InterpolationType::LINEAR:
		this->_Interp = std::make_shared<QuantLib::LinearInterpolation>(
			QuantLib::LinearInterpolation(tenors.begin(), tenors.end(), rates.begin()));
		break;
	case InterpolationType::CUBIC_SPLINE:
		this->_Interp = std::make_shared<QuantLib::CubicNaturalSpline>(
			QuantLib::CubicNaturalSpline(tenors.begin(), tenors.end(), rates.begin()));
		break;
	}
}
// Constructors/Destructor:
ZeroCurve::ZeroCurve() : _ZeroRates(), _Interp()
{

}
ZeroCurve::ZeroCurve(const InterpolationType& interp) : _ZeroRates(), _Interp()
{

}
ZeroCurve::ZeroCurve(const ZeroCurve& crv) : _ZeroRates(crv._ZeroRates), _Interp(crv._Interp)
{

}
ZeroCurve::~ZeroCurve()
{

}
// Accessors:
const std::unordered_map<double, double>& ZeroCurve::ZeroRates() const
{
	return this->_ZeroRates;
}
double ZeroCurve::ZeroRate(double tenor) const
{
	auto match = this->_ZeroRates.find(tenor);
	if (match != this->_ZeroRates.end())
	{
		return match->second;
	}
	else
	{
		return this->_Interp->operator()(tenor, true);
	}
}
double ZeroCurve::ZeroRate(const QuantLib::Date& settle, const QuantLib::Date& expiry) const
{
	double tenor = QuantLib::Actual365Fixed().yearFraction(settle, expiry);
	return this->ZeroRate(tenor);
}
double ZeroCurve::DiscountFactor(double tenor) const
{
	double rate = this->ZeroRate(tenor);
	return std::pow(1 + rate, -tenor);
}
double ZeroCurve::DiscountFactor(const QuantLib::Date& settle, const QuantLib::Date& expiry) const
{
	double tenor = QuantLib::Actual365Fixed().yearFraction(settle, expiry);
	return this->DiscountFactor(tenor);
}
// Mutators:
void ZeroCurve::ZeroRates(const std::unordered_map<double, double>& crv)
{
	this->_ZeroRates = crv;
}
void ZeroCurve::AddZeroRate(double rate, const QuantLib::Date& settle, const QuantLib::Date& expiry)
{
	double tenor = ZeroCurve::Tenor(settle, expiry);
	this->AddZeroRate(rate, tenor);
}
void ZeroCurve::AddZeroRate(double rate, double tenor)
{
	if (this->_ZeroRates.find(tenor) != this->_ZeroRates.end())
	{
		this->_ZeroRates.emplace(tenor, rate);
	}
}
void ZeroCurve::ParseFile(const std::string &path)
{
	if (this->_ZeroRates.size())
	{
		this->_ZeroRates.clear();
	}
	std::fstream file(path);
	if (!file)
	{
		throw std::exception("Could not open ZeroRates file.");
	}
	std::string cell, line;
	double tenor, rate;
	std::getline(file, line);
	while (!file.eof())
	{
		std::getline(file, line);
		std::stringstream stream(line);
		std::getline(stream, cell, ',');
		if (cell.empty())
		{
			break;
		}
		tenor = std::stod(cell);
		std::getline(stream, cell, ',');
		if (cell.empty())
		{
			break;
		}
		rate = std::stod(cell);
		this->_ZeroRates.emplace(tenor, rate);
	}
}
// Interface Methods:
double ZeroCurve::DiscountFactor(double rate, double tenor)
{
	return std::pow(1 + rate, -tenor);
}
double ZeroCurve::Tenor(const QuantLib::Date &settle, const QuantLib::Date &expiry)
{
	return QuantLib::Actual365Fixed().yearFraction(settle, expiry);
}
double ZeroCurve::Price() const
{
	return 0;
}
double ZeroCurve::Delta() const
{
	return 0;
}
double ZeroCurve::Gamma() const
{
	return 0;
}
double ZeroCurve::Theta() const
{
	return 0;
}
double ZeroCurve::Vega() const
{
	return 0;
}
double ZeroCurve::Rho() const
{
	return 0;
}
// Overloaded Operators:
ZeroCurve& ZeroCurve::operator=(const ZeroCurve& curve)
{
	if (this != &curve)
	{
		this->_ZeroRates = curve._ZeroRates;
	}
	return *this;
}