#ifndef PNLFILE_HPP
#define PNLFILE_HPP

#include <fstream>
#include "FileType.hpp"
#include "Hashers.hpp"
#include "PNLFileRow.hpp"

class PNLFile : FileType
{
private:
	std::vector<QuantLib::Date> _SortedDates;
	static std::string _Headers;
	std::unordered_map<QuantLib::Date, PNLFileRow, QDateHash> _Rows;
	void _SortDates();
public:
	// Constructors/Destructor:
	PNLFile();
	PNLFile(const std::string&);
	PNLFile(const PNLFile&);
	virtual ~PNLFile();
	// Accessors:
	const std::unordered_map<QuantLib::Date, PNLFileRow, QDateHash>& Rows() const;
	// Mutators:
	void AppendRow(const PNLFileRow &row);
	void ParseFile(const std::string &path);
	// Overloaded Operators:
	PNLFile& operator=(const PNLFile&);
	friend std::ostream& operator<<(std::ostream& stream, const PNLFile &file)
	{
		stream << PNLFile::_Headers << '\n';
		for (auto &row : file.Rows())
		{
			stream << row.second << '\n';
		}
		return stream;
	}
};


#endif
