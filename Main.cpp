/* Main.cpp
Description:
	*


*/

// NOTE: Need to set "/std:c++latest" as compiler flag to compile the <filesystem> library.

#include <fstream>
#include <string>
#include "ComponentWeightsFile.hpp"
#include "DispersionTrade.hpp"
#include "OptionChains.hpp"

int main()
{
	// 1) Pull in S&P 100 tickers and weights from local file:
	std::string indexName("^OEX");
	ComponentWeightsFile tickerFile("SP_100.csv");
	// Find expiration date where all components and index options are trading:
	auto result = tickerFile.AllComponentsAvailable("04_08_2020", indexName);
	// 2) Determine trade that finds most out-of-line DispersionTrade 
	// (implied correlation outside of [-1, 1], or highest absolute correlation):
	DispersionTradeAttributes attrs;
	attrs.IndexName(indexName);
	attrs.IndexOption(Option());
	std::unordered_map<std::string, std::pair<Option, double>> constituents;
	for (auto &entry : tickerFile.Tickers())
	{
		constituents.emplace(entry.second.Ticker(), std::make_pair(Option(), entry.second.Weight()));
	}
	attrs.ConstituentOptions(constituents);
	auto optimal_trade = DispersionTrade::OptimalDispersionTrade("04_08_2020", result.first, attrs);
	// 3) Pull in option chains for optimal value date:
	
	// 4) Calculate profit-and-loss, trade "greeks" for each available revalue date,
	// Print to file:


	// Test pulling in option chains for value date:
	OptionChains chains("04_09_2020", 2, 18, 2021);
	std::ofstream testFile("option_chains.csv");
	testFile << chains;
	testFile.close();

	return 0;
}