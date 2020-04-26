#include "ApplicationSteps.hpp"

// Private Functions:
void ApplicationSteps::_GetAllOptionChains()
{
	// Pull all option chains for all value dates:
	auto valueDate = this->_Gen.ValueDate();
	OptionChainPathGenerator gen(this->_AllChainFolder);
	// Pull in option chains for value date:
	while (valueDate <= this->_GUI.EndValueDate())
	{
		this->_Chains.emplace(valueDate, SubChainMap());
		auto vdFolder = FileType::DateToString(valueDate, '_');
		gen.ValueDate(valueDate);
		auto fullPath = this->_AllChainFolder + "\\" + vdFolder;
		if (FileType::PathExists(fullPath))
		{
			// Pull all option chains for expiration date:
			for (const auto &expDateFolder : std::filesystem::directory_iterator(fullPath))
			{
				auto expDate = OptionChainPathGenerator::ExtractExpirationDate_Folder(expDateFolder.path().string());
				gen.ExpirationDate(expDate);
				this->_Chains[valueDate].emplace(expDate, OptionChains(gen));
			}
		}
		valueDate += 1;
	}
}
void ApplicationSteps::_EnsureAllPathsPresent()
{
	// Ensure all necessary files/folders present:
	std::vector<std::string> targets = { "SP_100.csv", "TimeSeries.csv", this->_AllChainFolder };
	std::vector<std::string> missing;
	for (auto target = targets.begin(); target != targets.end(); ++target)
	{
		if (!FileType::PathExists(*target))
		{
			missing.push_back(*target);
		}
	}
	if (missing.size())
	{
		std::ostringstream message(std::ios_base::ate);
		message << "The following files or folders are missing:\n\n";
		for (auto &path : missing)
		{
			message << path << '\n';
		}
		this->_GUI.DisplayExceptionMessage(message.str().c_str(), true);
	}
}
// Constructors/Destructor:
ApplicationSteps::ApplicationSteps(const std::string &allChainFolder) : _AllChainFolder(allChainFolder),
	_Chains(), _EquityTimeSeries(), _GUI(), _Gen(allChainFolder), _Portfolio(), _WeightsFile()
{

}
ApplicationSteps::~ApplicationSteps()
{

}
// Interface Methods:
void ApplicationSteps::DisplayStartScreen()
{
	this->_GUI.DisplayStartScreen();
}
void ApplicationSteps::GetArgumentsFromUser()
{
	std::cout << "----- Getting arguments from user ----" << std::endl;
	// Get command line arguments from user:
	this->_GUI.DisplayStartScreen();
	this->_GUI.GetStartValueDate();
	this->_GUI.GetEndValueDate();
	this->_GUI.GetOutputPath();
}
void ApplicationSteps::AcquireAllData()
{
	std::cout << "----- Acquiring all relevant data ----" << std::endl;
	// Ensure all files and folders are present:
	this->_EnsureAllPathsPresent();
	// Parse all files used in application:
	this->_WeightsFile.ParseFile("SP_100.csv");
	this->_EquityTimeSeries.ParseFile("TimeSeries.csv");
	this->_Gen.ValueDate(this->_GUI.StartValueDate());
	// Pull all option chains:
	this->_GetAllOptionChains();
	// **Testing: Print out all files:
	std::ofstream out("WeightsFile_Out.csv");
	out << this->_WeightsFile;
	out.close();
	std::ofstream out_2("TimeSeries_Out.csv");
	out_2 << this->_EquityTimeSeries;
	out_2.close();
	

}
void ApplicationSteps::FindOptimalDispersionTrade()
{
	// Find expiration with greatest # of options available:
	std::cout << "----- Finding optimal disperion trade for " << FileType::DateToString(this->_Gen.ValueDate(),'\\') << "----" << std::endl;
	auto result = this->_WeightsFile.AllComponentsAvailable(this->_Gen, "^OEX");
	std::cout << "Using expiration date: " << FileType::DateToString(result.first.ExpirationDate(), '\\') << std::endl;
	std::cout << "with " << result.second.size() << " total options." << std::endl;
	// Find the optimal strikes for the dispersion trade:
	std::cout << "Optimal strike: " << std::endl;

}
void ApplicationSteps::CalculatePNLForTradePeriod()
{
	std::cout << "----- Calculating trade PNL for value dates ----" << std::endl;
}
void ApplicationSteps::OutputFiles()
{
	std::cout << "----- Outputting all files ----" << std::endl;
}
void ApplicationSteps::PrintResultSummary()
{
	std::cout << "----- Summary ----" << std::endl;
}