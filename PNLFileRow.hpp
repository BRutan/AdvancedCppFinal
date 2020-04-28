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
	// Greeks:
	double _Delta, _Gamma, _Vega, _Rho, _Theta;
public:
	// Constructors/Destructor:
	PNLFileRow();
	PNLFileRow(const std::string &);
	PNLFileRow(const PNLFileRow&);
	virtual ~PNLFileRow();
	// Accessors:
	double Delta() const;
	double Gamma() const;
	double Rho() const;
	double Vega() const;
	double Theta() const;
	double ImpliedCorrelation() const;
	double PriceChg() const;
	double PercentChg() const;
	const QuantLib::Date& ValueDate() const;
	const std::string& Ticker() const;
	double Price() const;
	// Mutators:
	void Delta(double);
	void Gamma(double);
	void Rho(double);
	void Vega(double);
	void Theta(double);
	void ParseRow(const std::string &row);
	void Price(double);
	void ImpliedCorrelation(double);
	void PriceChg(double);
	void PercentChg(double);
	void ValueDate(const QuantLib::Date&);
	void Ticker(const std::string&);
	void ParseRow(const std::string &row);
	void Price(double);
	// Overloaded Operators:
	PNLFileRow& operator=(const PNLFileRow&);
	friend std::ostream& operator<<(std::ostream &stream, const PNLFileRow &row)
	{
		stream << FileType::DateToString(row._ValueDate, '//') << ',' << row._Ticker << ',' << row._Price;
		stream << ',' << row._ChgPrice << ',' << row._ChgPercent << ',' << row._ImpliedCorrel;
		stream << ',' << row._Delta << ',' << row._Gamma << ',' << row._Rho;
		stream << ',' << row._Theta << ',' << row._Vega; 
		return stream;
	}
};


#endif
