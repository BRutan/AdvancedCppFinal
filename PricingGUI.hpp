#ifndef PRICINGGUI_HPP
#define PRICINGGUI_HPP

#include <ql/time/date.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include "OptionChainPathGenerator.hpp"

class PricingGUI
{
private:
	QuantLib::Date _StartValueDate;
	QuantLib::Date _EndValueDate;
	std::string _OutputPath;
	PricingGUI& operator=(const PricingGUI&) = delete;
	PricingGUI(const PricingGUI&) = delete;
public:
	// Constructors/Destructor:
	PricingGUI();
	virtual ~PricingGUI();
	// Accessors:
	const QuantLib::Date& StartValueDate() const;
	const QuantLib::Date& EndValueDate() const;
	const std::string& OutputPath() const;
	// Mutators:
	void GetOutputPath();
	void GetEndValueDate();
	void GetStartValueDate();
	// Interface Methods:
	void DisplayStartScreen() const;
};

#endif
