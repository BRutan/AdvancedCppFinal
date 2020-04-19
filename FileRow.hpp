#ifndef FILEROW_HPP
#define FILEROW_HPP

class FileRow
{
public:
	FileRow()
	{

	}
	virtual ~FileRow()
	{

	}
	virtual void ParseRow(const std::string& row) = 0;
};


#endif
