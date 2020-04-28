#ifndef PNLFILEROW_HPP
#define PNLFILEROW_HPP

#include <ql/time/date.hpp>
#include "FileRow.hpp"
#include "FileType.hpp"

class PNLFileRow : public FileRow
{
private:
	QuantLib::Date _ValueDate;
	std::string _Ticker;
	double _Price;
	double _ChgPrice, _ChgPercent, _ImpliedCorrel;
public:
	// Constructors/Destructor:
	PNLFileRow();
	PNLFileRow(const std::string &);
	PNLFileRow(const PNLFileRow&);
	virtual ~PNLFileRow();
	// Accessors:
	double ImpliedCorrelation() const;
	double PriceChg() const;
	double PercentChg() const;
	const QuantLib::Date& ValueDate() const;
	const std::string& Ticker() const;
	double Price() const;
	// Mutators:
	void ParseRow(const std::string &row);
	void Price(double);
	void ImpliedCorrelation(double);
	void PriceChg(double);
	void PercentChg(double);
	void ValueDate(const QuantLib::Date&);
	void Ticker(const std::string&);
	// Overloaded Operators:
	PNLFileRow& operator=(const PNLFileRow&);
	friend std::ostream& operator<<(std::ostream &stream, const PNLFileRow &row)
	{
		stream << FileType::DateToString(row._ValueDate, '//') << ',' << row._Ticker << ',' << row._Price;
		stream << ',' << row._ChgPrice << ',' << row._ChgPercent << ',' row._ImpliedCorrel;
		return stream;
	}
};


#endif
