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
#pragma region Constructors/Destructor:
	AssetFactory();
	AssetFactory(bool generateLong, const ZeroCurve& riskFree, const QuantLib::Date &settle, const QuantLib::Date &expiry);
	AssetFactory(const AssetFactory&);
	virtual ~AssetFactory();
#pragma endregion
#pragma region Accessors:
	const QuantLib::Date& Expiration() const;
	bool GeneratingLong() const;
	const ZeroCurve& RiskFreeCurve() const;
	const QuantLib::Date& Settlement() const;
#pragma endregion
#pragma region Mutators
	void Expiration(const QuantLib::Date&);
	void GeneratingLong(bool);
	void RiskFree(const ZeroCurve&);
	void Settlement(const QuantLib::Date&);
#pragma endregion
#pragma region Options
	Option GenerateOption(bool isCall, const OptionChainRow &option_data, const EquityAttributes& attr) const;
#pragma endregion
#pragma region IndexDispersion
	IndexDispersion GenerateDispersion(const std::string &indexSymbol, double indexStrike, const ComponentWeightsFile& weights, const OptionChains& chains,
		const std::unordered_map<std::string, EquityAttributes>& underlyings) const;
	IndexDispersionAttributes GenerateDispersionAttributes(const std::string &indexSymbol, const ComponentWeightsFile& weights,
		const std::unordered_map<std::string, EquityAttributes>& underlyings) const;
	IndexDispersion GenerateDispersion(const OptionChains& chains, const IndexDispersionAttributes&) const;
	std::pair<IndexDispersion, double> OptimalDispersionTrade(const OptionChainPathGenerator &gen,
		const IndexDispersionAttributes &attrs, const std::unordered_map<std::string, EquityAttributes>& underlyings, double assumedIV);
#pragma endregion
#pragma region Static Methods
	static double NormCDF(double z);
#pragma endregion
#pragma region Operators
	AssetFactory& operator=(const AssetFactory&);
#pragma endregion
};

#endif