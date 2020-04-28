#include "PNLFile.hpp"

std::string PNLFile::_Headers = "ValueDate,Ticker,Price,PriceChg,PercentChg,ImpliedCorrelation";

void PNLFile::_SortDates()
{
	this->_SortedDates.clear();
	for (auto &entry : this->_Rows)
	{
		this->_SortedDates.push_back(entry.first);
	}
	std::sort(this->_SortedDates.begin(), this->_SortedDates.end());
}
// Constructors/Destructor:
PNLFile::PNLFile() : FileType(), _Rows(), _SortedDates()
{

}
PNLFile::PNLFile(const std::string &path) : _Rows(), FileType(), _SortedDates()
{
	this->ParseFile(path);
}
PNLFile::PNLFile(const PNLFile &file) : _Rows(), FileType(file), _SortedDates()
{

}
PNLFile::~PNLFile()
{

}
// Accessors:
const std::unordered_map<QuantLib::Date, PNLFileRow>& PNLFile::Rows() const
{
	return this->_Rows;
}
// Mutators:
void PNLFile::AppendRow(const PNLFileRow &row)
{
	if (this->_Rows.find(row.ValueDate()) == this->_Rows.end())
	{
		this->_Rows.emplace(row.ValueDate(), row);
		this->_SortedDates.push_back(row.ValueDate());
		std::sort(this->_SortedDates.begin(), this->_SortedDates.end());
	}
}
void PNLFile::ParseFile(const std::string &path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::exception("Could not open file at path.");
	}
	std::string line;
	std::getline(file, line);
	while (!file.eof())
	{
		std::getline(file, line);
		PNLFileRow row(line);
		this->_Rows.emplace(row.ValueDate(), row);
	}
	file.close();
	this->_SortDates();
}
// Overloaded Operators:
PNLFile& PNLFile::operator=(const PNLFile &file)
{
	if (this != &file)
	{
		FileType::operator=(file);
	}
	return *this;
}
