#include "ApplicationSteps.hpp"

// Private Functions:
bool ApplicationSteps::_GetOptionChains_Expiry(const QuantLib::Date &expiry)
{
	OptionChainPathGenerator gen(this->_Gen);
	gen.ExpirationDate(expiry);
	if (!FileType::PathExists(gen.ExpirationDateFolder()))
	{
		return false;
	}
	this->_TradeChains = OptionChains(gen);
	return true;
}
bool ApplicationSteps::_GetOptionChains_ValueDate(const QuantLib::Date &valueDate)
{
	OptionChainPathGenerator gen(this->_AllChainFolder);
	gen.ValueDate(valueDate);
	auto vdFolder = gen.ValueDateFolder();
	if (FileType::PathExists(vdFolder))
	{
		// Pull all option chains for all expiration dates:
		for (const auto &expDateFolder : std::filesystem::directory_iterator(vdFolder))
		{
			auto expDate = OptionChainPathGenerator::ExtractExpirationDate_Folder(expDateFolder.path().string());
			gen.ExpirationDate(expDate);
			this->_ValueDateChains.emplace(expDate, OptionChains(gen));
		}
	}
	else
	{
		return false;
	}
	return true;
}
void ApplicationSteps::_GetAllOptionChains()
{
	// Pull all option chains for all value dates:
	auto valueDate = this->_Gen.ValueDate();
	OptionChainPathGenerator gen(this->_AllChainFolder);
	// Pull in option chains for value date:
	while (valueDate <= this->_GUI.EndValueDate())
	{
		gen.ValueDate(valueDate);
		auto vdFolder = gen.ValueDateFolder();
		if (FileType::PathExists(vdFolder))
		{
			// Pull all option chains for all expiration dates:
			this->_AllChains.emplace(valueDate, SubChainMap());
			// Pull in all chains for each expiration date (one OptionChains object per expiration date):
			for (const auto &expDateFolder : std::filesystem::directory_iterator(vdFolder))
			{
				auto expDate = OptionChainPathGenerator::ExtractExpirationDate_Folder(expDateFolder.path().string());
				gen.ExpirationDate(expDate);
				this->_AllChains[valueDate].emplace(expDate, OptionChains(gen));
			}
		}
		valueDate += 1;
	}
}
void ApplicationSteps::_EnsureAllPathsPresent()
{
	// Ensure all necessary files/folders present:
	std::vector<std::string> targets = { "SP_100.csv", "TimeSeries.csv", this->_AllChainFolder, "RiskFree.csv" };
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
void ApplicationSteps::_UpdateUnderlyings(const QuantLib::Date &valueDate)
{
	auto prices = this->_EquityTimeSeries.GetSeriesForDate(valueDate);
	this->_Underlyings.clear();
	for (auto &entry : this->_WeightsFile.Tickers())
	{
		auto price = prices[entry.first];
		this->_Underlyings.emplace(entry.first,
			EquityAttributes(price, valueDate, true, 0, entry.second.DividendYield()));
	}
}
// Constructors/Destructor:
ApplicationSteps::ApplicationSteps(const std::string &allChainFolder) : _AllChainFolder(allChainFolder),
	_AllChains(), _EquityTimeSeries(), _GUI(), _Gen(allChainFolder), _Portfolio(), _TradeChains(), _ValueDateChains(), _WeightsFile("^OEX"),
	_TradeFactory(), _Underlyings(), _OptimalTrade()
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
	std::cout << "^OEX (S&P 100) tickers, weightings, dividend rates (SP_100.csv)..." << std::endl;
	this->_WeightsFile.ParseFile("SP_100.csv");
	std::cout << "^OEX and component time series..." << std::endl;
	this->_EquityTimeSeries.ParseFile("TimeSeries.csv");
	this->_Gen.ValueDate(this->_GUI.StartValueDate());
	this->_RiskFree.ParseFile("RiskFree.csv");
	// Get all underlying info from equity time series file for start value date and weights file:
	
}
void ApplicationSteps::FindOptimalDispersionTrade()
{
	// Find expiration with greatest # of options available:
	std::cout << "----- Finding expiration with greatest # of component options for " << FileType::DateToString(this->_Gen.ValueDate(), '\\') << " value date----" << std::endl;
	auto result = this->_WeightsFile.AllComponentsAvailable(this->_Gen, &QuantLib::Date(17, QuantLib::April, 2020));
	std::cout << "Using expiration date: " << FileType::DateToString(result.first.ExpirationDate(), '\\') << std::endl;
	std::cout << "with " << result.second.size() << " total options." << std::endl;
	std::cout << "----- Finding optimal disperion trade for " << FileType::DateToString(this->_Gen.ValueDate(), '\\') << "----" << std::endl;
	auto attr = this->_TradeFactory.GenerateDisperionAttributes("^OEX", this->_WeightsFile, this->_Underlyings);
	auto optimal_trade = IndexDispersion::OptimalDispersionTrade(this->_Gen, attr);
	this->_OptimalTrade = optimal_trade.first;
	auto index_attr = dynamic_cast<OptionAttributes*>(this->_OptimalTrade.IndexOption().Attributes().get());
	auto trade_attr = dynamic_cast<IndexDispersionAttributes*>(this->_OptimalTrade.Attributes().get());

	std::cout << "Optimal trade has implied correlation of " << std::setprecision(2) << optimal_trade.second << std::endl;
	std::cout << "with index strike " << index_attr->Strike() << std::endl;
	std::cout << "net premium " << trade_attr->Price() << std::endl;
	// Pull all option chains for expiration date:


	// Find the optimal strikes for the dispersion trade:
	//IndexDispersion::OptimalDispersionTrade(this->_Gen, );
	
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