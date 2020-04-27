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
	steps.AcquireBackendData();
	steps.FindOptimalDispersionTrade();
	steps.AcquireTradeData();
	//steps.CalculatePNLForTradePeriod();
	//steps.OutputFiles();
	//steps.PrintResultSummary();
	/*
	// Find expiration date where all components and index options are trading:
	// 2) Determine trade that finds most out-of-line IndexDispersion 
	// (implied correlation outside of [-1, 1], or highest absolute correlation):
	IndexDispersionAttributes attrs;
	attrs.IndexName(indexName);
	attrs.IndexOption(Option());
	std::unordered_map<std::string, std::pair<Option, double>> constituents;
	for (auto &entry : tickerFile.Tickers())
	{
		constituents.emplace(entry.second.Ticker(), std::make_pair(Option(), entry.second.Weight()));
	}
	attrs.ConstituentOptions(constituents);
	auto optimal_trade = IndexDispersion::OptimalDispersionTrade(result.first, attrs);
	// 3) Pull in option chains for optimal value date:
	
	// 4) Calculate profit-and-loss, trade "greeks" for each available revalue date,
	
	*/

	return 0;
}