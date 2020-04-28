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
	this->_TradeChains = OptionChains(true, gen);
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
			this->_ValueDateChains.emplace(expDate, OptionChains(true, gen));
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
				this->_AllChains[valueDate].emplace(expDate, OptionChains(true, gen));
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
		this->_Underlyings.emplace(entry.first, EquityAttributes(price, valueDate, true, 0, entry.second.DividendYield()));
	}
}
// Constructors/Destructor:
ApplicationSteps::ApplicationSteps(const std::string &allChainFolder) : _AllChainFolder(allChainFolder),
_AllChains(), _EquityTimeSeries(), _GUI(), _Gen(allChainFolder), _Portfolio(), _TradeChains(), _ValueDateChains(), _WeightsFile("^OEX"),
_TradeFactory(), _Underlyings(), _OptimalTrade(), _PNL()
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
	this->_UpdateUnderlyings(this->_Gen.ValueDate());
}
void ApplicationSteps::FindOptimalDispersionTrade()
{
	// Find expiration with greatest # of options available:
	this->_TradeFactory.RiskFree(this->_RiskFree);
	std::cout << "----- Finding expiration with greatest # of component options for " << FileType::DateToString(this->_Gen.ValueDate(), '\\') << " value date----" << std::endl;
	auto result = this->_WeightsFile.AllComponentsAvailable(this->_Gen, &QuantLib::Date(17, QuantLib::April, 2020));
	std::cout << "Using expiration date: " << FileType::DateToString(result.first.ExpirationDate(), '\\') << std::endl;
	std::cout << "with " << result.second.size() << " total options." << std::endl;
	auto attr = this->_TradeFactory.GenerateDispersionAttributes("^OEX", this->_WeightsFile, this->_Underlyings);
	attr.ExpirationDate(result.first.ExpirationDate());
	attr.SettlementDate(this->_GUI.StartValueDate());
	this->_TradeFactory.Expiration(attr.ExpirationDate());
	this->_TradeFactory.Settlement(attr.SettlementDate());
	this->_Gen.ExpirationDate(attr.ExpirationDate());
	this->_Gen.ValueDate(attr.SettlementDate());
	std::cout << "----- Finding optimal disperion trade for " << FileType::DateToString(this->_Gen.ValueDate(), '\\') << "----" << std::endl;
	auto results = this->_TradeFactory.OptimalDispersionTrade(this->_Gen, attr, this->_Underlyings, .3);
	this->_OptimalTrade = results.first;
	auto index_attr = dynamic_cast<OptionAttributes*>(this->_OptimalTrade.IndexOption().Attributes().get());
	auto trade_attr = dynamic_cast<IndexDispersionAttributes*>(this->_OptimalTrade.Attributes().get());
	std::cout << "Optimal trade has implied correlation of " << std::fixed << std::setprecision(2) << this->_OptimalTrade.ImpliedCorrelation() << std::endl;
	std::cout << "index strike: " << std::fixed << std::setprecision(2) << index_attr->Strike() << std::endl;
	std::cout << "net premium: " << std::fixed << std::setprecision(2) << trade_attr->Price() << std::endl;
	std::cout << "approximate delta: " << std::fixed << std::setprecision(2) << results.second << std::endl;
}
void ApplicationSteps::CalculatePNLForTradePeriod()
{
	std::cout << "----- Calculating trade PNL for value dates ----" << std::endl;
	auto indexStrike = std::dynamic_pointer_cast<OptionAttributes>(this->_OptimalTrade.IndexOption().Attributes())->Strike();
	auto indexSymbol = std::dynamic_pointer_cast<IndexDispersionAttributes>(this->_OptimalTrade.Attributes())->IndexName();
	auto copy = *std::dynamic_pointer_cast<IndexDispersionAttributes>(this->_OptimalTrade.Attributes());
	for (auto startDate = this->_Gen.ValueDate() + 1; startDate < this->_GUI.EndValueDate(); ++startDate)
	{
		this->_Gen.ValueDate(startDate);
		// Skip value date if folder not present:
		if (!FileType::PathExists(this->_Gen.ValueDateFolder()) || !FileType::PathExists(this->_Gen.ExpirationDateFolder()))
		{
			std::cerr << "Skipping value date " << FileType::DateToString(this->_Gen.ValueDate(), '//') << std::endl;
			std::cerr << "no data available for " << FileType::DateToString(this->_Gen.ExpirationDate(), '//') << " expiration." << std::endl;
			continue;
		}
		this->_TradeFactory.Settlement(startDate);
		OptionChains chains(true, this->_Gen);
		if (chains.Files().size() == 0)
		{
			std::cerr << "Skipping value date " << FileType::DateToString(this->_Gen.ValueDate(), '//') << std::endl;
			std::cerr << "no data available for " << FileType::DateToString(this->_Gen.ExpirationDate(), '//') << " expiration." << std::endl;
			continue;
		}
		// Update trade value data, calculate pnl over period:
		auto newDisp = this->_TradeFactory.GenerateDispersion(chains, copy);
		copy = *std::dynamic_pointer_cast<IndexDispersionAttributes>(newDisp.Attributes());
		// Calculate PNL:
		auto row = this->_OptimalTrade - newDisp;
		this->_PNL.AppendRow(row);
	}
}
void ApplicationSteps::OutputFiles()
{
	std::cout << "----- Final Results----" << std::endl;
	std::cout << "Outputting PNL file to " << std::endl;
	std::cout << this->_GUI.OutputPath() << std::endl;
	std::ofstream file(this->_GUI.OutputPath());
	if (!file)
	{
		throw std::exception("Could not open file at path.");
	}
	file << this->_PNL;
	file.close();
}
void ApplicationSteps::PrintResultSummary()
{
	std::cout << "----- Summary ----" << std::endl;
}