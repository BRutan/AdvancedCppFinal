#ifndef TRADEGENERATOR_HPP
#define TRADEGENERATOR_HPP

#include <ql/time/date.hpp>
#include "ComponentWeightsFileRow.hpp"
#include "ComponentWeightsFile.hpp"
#include "Equity.hpp"
#include "IndexDispersion.hpp"
#include "OptionChainRow.hpp"
#include "OptionChains.hpp"
#include "OptionChain.hpp"
#include "TimeSeries.hpp"
#include "ZeroCurve.hpp"

class AssetFactory
{
private:
	bool _GenerateLong;
	ZeroCurve _RiskFreeCurve;
	QuantLib::Date _Settle, _Expiry;
public:
	// Constructors/Destructor:
	AssetFactory();
	AssetFactory(bool generateLong, const ZeroCurve& riskFree, const QuantLib::Date &settle, const QuantLib::Date &expiry);
	AssetFactory(const AssetFactory&);
	virtual ~AssetFactory();
	// Accessors:
	const QuantLib::Date& Expiration() const;
	bool GeneratingLong() const;
	const ZeroCurve& RiskFreeCurve() const;
	const QuantLib::Date& Settlement() const;
	// Mutators:
	void Expiration(const QuantLib::Date&);
	void GeneratingLong(bool);
	void RiskFree(const ZeroCurve&);
	void Settlement(const QuantLib::Date&);
	// Interface Methods:
	Option GenerateOption(bool isCall, const OptionChainRow &option_data, const EquityAttributes& attr) const;
	IndexDispersion GenerateDispersion(const std::string &indexSymbol, double indexStrike, const ComponentWeightsFile& weights, const OptionChains& chains,
		const std::unordered_map<std::string, EquityAttributes>& underlyings) const;
	IndexDispersionAttributes GenerateDisperionAttributes(const std::string &indexSymbol, const ComponentWeightsFile& weights,
		const std::unordered_map<std::string, EquityAttributes>& underlyings) const;
	/*
	template<unsigned long numcols>
	Equity GenerateEquity(const TimeSeries<numcols> &series, const QuantLib::Date &valueDate);
	*/
	AssetFactory& operator=(const AssetFactory&);
};

#endif