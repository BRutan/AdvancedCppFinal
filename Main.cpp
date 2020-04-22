/* Main.cpp
Description:
	*


*/

// NOTE: Need to set "/std:c++latest" as compiler flag to compile the <filesystem> library.

#include <fstream>
#include <string>
#include "OptionChains.hpp"

#include "TickersFile.hpp"

// TODO:
// 1. Implement gregorian_date as key in FileType.
// 2. 

int main()
{
	// 1) Pull in S&P 100 tickers and weights from local file:
	TickersFile tickerFile("");
	// 2) Determine trade that finds most out-of-line DispersionTrade (implied correlation outside of [-1, 1]):
	
	// 3) Pull in option chains for optimal value date:
	
	
	// Test pulling in option chains for value date:
	OptionChains chains("04_09_2020", 2, 18, 2021);
	std::ofstream testFile("option_chains.csv");
	testFile << chains;
	testFile.close();

	return 0;
}