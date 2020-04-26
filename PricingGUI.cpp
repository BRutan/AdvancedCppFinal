#include "PricingGUI.hpp"


	// Constructors/Destructor:
PricingGUI::PricingGUI() : _StartValueDate(), _EndValueDate(), _OutputPath()
{
	
}
PricingGUI::~PricingGUI()
{

}
// Accessors:
const QuantLib::Date& PricingGUI::StartValueDate() const
{
	return this->_StartValueDate;
}
const QuantLib::Date& PricingGUI::EndValueDate() const
{
	return this->_EndValueDate;
}
const std::string& PricingGUI::OutputPath() const
{
	return this->_OutputPath;
}
// Mutators:
void PricingGUI::GetOutputPath()
{
	// Request output path from user via stdin:
	std::string outputPath;
	std::cout << "Please enter output path for PNL and risk calculations:" << std::endl;
	std::cin >> outputPath;
	while (!std::filesystem::exists(outputPath))
	{
		std::cout << "Output path does not exist, please enter another: " << std::endl;
		std::cin >> outputPath;
	}
	this->_OutputPath = outputPath;
}
void PricingGUI::GetEndValueDate()
{
	// Request end value date user via stdin:
	std::string dateStr;
	std::cout << "Please enter final value date for dispersion trade (MM/DD/YYYY):" << std::endl;
	std::cin >> dateStr;
	/*
	// Ensure date is valid:
	while (!std::filesystem::exists(outputPath))
	{
		std::cout << "Output path does not exist, please enter another: " << std::endl;
		std::cin >> outputPath;
	}*/
	this->_EndValueDate = OptionChainPathGenerator::StringToDate(dateStr, '//');
}
void PricingGUI::GetStartValueDate()
{
	// Request start value date user via stdin:
	std::string dateStr;
	std::cout << "Please enter initial trade date for dispersion trade (MM/DD/YYYY):" << std::endl;
	std::cin >> dateStr;
	/*
	// Ensure date is valid:
	while (!std::filesystem::exists(outputPath))
	{
		std::cout << "Output path does not exist, please enter another: " << std::endl;
		std::cin >> outputPath;
	}*/
	this->_StartValueDate = OptionChainPathGenerator::StringToDate(dateStr, '//');
}
void PricingGUI::DisplayStartScreen() const
{
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "^OEX Dispersion Trade PNL Generator" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
}