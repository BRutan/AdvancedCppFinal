#ifndef APPLICATIONSTEPS_HPP
#define APPLICATIONSTEPS_HPP

#include <ql/time/date.hpp>
#include <fstream>
#include <string>
#include "ComponentWeightsFile.hpp"
#include "IndexDispersion.hpp"
#include "Option.hpp"
#include "OptionChains.hpp"
#include "OptionChainPathGenerator.hpp"
#include "Portfolio.hpp"
#include "PricingGUI.hpp"
#include "TimeSeries.hpp"

// Central application controller:
class ApplicationSteps
{
private:
	explicit ApplicationSteps(const ApplicationSteps&) = delete;
	ApplicationSteps& operator=(const ApplicationSteps&) = delete;
	// Variables:
	ComponentWeightsFile _WeightsFile;
	OptionChains _Chains;
	OptionChainPathGenerator _Gen;
	Portfolio _Portfolio;
	PricingGUI _GUI;
	TimeSeries<101> _EquityTimeSeries;
public:
	// Constructors/Destructor:
	ApplicationSteps();
	~ApplicationSteps();
	// Interface Methods:
	void GetArgumentsFromUser();
	void AcquireAllData();
	void FindOptimalDispersionTrade();
	void CalculatePNLForTradePeriod();
	void OutputFiles();
	void PrintResultSummary();
};


#endif
