#include "PricingGUI.hpp"


	// Constructors/Destructor:
PricingGUI::PricingGUI() : _ValueDate(), _OutputPath()
{

}
PricingGUI::~PricingGUI()
{

}
// Accessors:
const QuantLib::Date PricingGUI::ValueDate() const
{
	return this->_ValueDate;
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
	std::cout << "Please enter output path for PNL:" << std::endl;
	std::cin >> outputPath;
	while (!std::filesystem::exists(outputPath))
	{
		std::cout << "Output path does not exist, please enter another: " << std::endl;
		std::cin >> outputPath;
	}
	this->_OutputPath = outputPath;
}
void PricingGUI::GetValueDate()
{
	// Request value date user via stdin:
	std::string dateStr;
	std::cout << "Please enter trade date for dispersion trade (MM//DD//YYYY):" << std::endl;
	std::cin >> dateStr;
	/*
	// Ensure date is valid:
	while (!std::filesystem::exists(outputPath))
	{
		std::cout << "Output path does not exist, please enter another: " << std::endl;
		std::cin >> outputPath;
	}*/
	this->_ValueDate = OptionChainPathGenerator::StringToDate(dateStr, '//');
}