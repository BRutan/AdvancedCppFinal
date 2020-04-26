#include "ApplicationSteps.hpp"


ApplicationSteps::ApplicationSteps() : _Chains(), _EquityTimeSeries(), _GUI(), _Gen(), _Portfolio(), _WeightsFile()
{

}
ApplicationSteps::~ApplicationSteps()
{

}
// Interface Methods:
void ApplicationSteps::GetArgumentsFromUser()
{
	// Get command line arguments from user:
	this->_GUI.DisplayStartScreen();
	this->_GUI.GetStartValueDate();
	this->_GUI.GetEndValueDate();
	this->_GUI.GetOutputPath();
}
void ApplicationSteps::AcquireAllData()
{
	// Parse all files used in application:
	this->_WeightsFile.ParseFile("SP_100.csv");
	this->_EquityTimeSeries.ParseFile("TimeSeries.csv");
	this->_Gen.ValueDate(this->_GUI.StartValueDate());

}
void ApplicationSteps::FindOptimalDispersionTrade()
{
	
}
void ApplicationSteps::CalculatePNLForTradePeriod()
{

}
void ApplicationSteps::OutputFiles()
{

}
void ApplicationSteps::PrintResultSummary()
{

}