/* Main.cpp
Description:
	* Query user to determine starting value date and ending value date.
	Find expiration date with greatest number of 


*/

// NOTE: Need to set "/std:c++latest" as compiler flag to compile the <filesystem> library.
#include <ql/auto_link.hpp>
#include "ApplicationSteps.hpp"

int main()
{
	// Get start and end value date from user:
	ApplicationSteps steps("OptionChains");
	steps.DisplayStartScreen();
	//steps.GetArgumentsFromUser();
	// **Testing 
	steps.OutputPath("Results");
	steps.StartValueDate(QuantLib::Date(9, QuantLib::Month::April, 2020));
	steps.EndValueDate(QuantLib::Date(25, QuantLib::Month::April, 2020));
	// ****
	steps.AcquireAllData();
	steps.FindOptimalDispersionTrade();
	steps.CalculatePNLForTradePeriod();
	steps.OutputFiles();
	steps.PrintResultSummary();
	return 0;
}