#include "BondFile.hpp"

std::string BondFile::_HeaderRow = "Name,Tenor,Yield,PresentValue";
// Constructors/Destructor:
BondFile::BondFile(const std::string& path)
{
	this->ParseFile(path);
}
BondFile::~BondFile()
{

}
// Interface Methods:
void BondFile::ParseFile(const std::string &path)
{
	// Expecting header Name,Tenor,Yield,PresentValue:
	if (this->_Data.size())
	{
		this->_Data.clear();
	}
	std::ifstream file(path);
	if (!file)
	{
		throw std::exception("Could not open file.");
	}
	std::string row;
	std::getline(file, row);
	while (!file.eof())
	{
		std::getline(file, row);
		auto newRow = new BondFileRow(row);
		this->_Data.emplace(newRow->Tenor(), newRow);
	}
	file.close();
	auto index = path.rfind('\\');
	std::string fileName((index != path.npos) ? path.substr(index + 1) : path);
	auto firstIDX = fileName.find_first_of('_');
	this->_ExtractAttributes(firstIDX, fileName);
}
// Overloaded Operators:
BondFile& BondFile::operator=(const BondFile &file)
{
	if (this != &file)
	{
		FileType::operator=(&file);
	}
	return *this;
}