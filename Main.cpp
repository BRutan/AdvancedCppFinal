/* Main.cpp
Description:
	*


*/

#include <fstream>
#include <string>
#include "OptionChains.hpp"

int main()
{
	// Test pulling in option chains for value date:
	OptionChains chains("04_09_2020", 2, 18, 2021);
	std::ofstream testFile("option_chains.csv");
	testFile << chains;
	testFile.close();


	return 0;
}