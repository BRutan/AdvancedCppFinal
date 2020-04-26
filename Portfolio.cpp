#include "Portfolio.hpp"

double Portfolio::Price() const
{

}
double Portfolio::Delta() const
{

}
double Portfolio::Gamma() const
{

}
double Portfolio::Theta() const
{

}
double Portfolio::Vega() const
{

}
double Portfolio::Rho() const
{

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