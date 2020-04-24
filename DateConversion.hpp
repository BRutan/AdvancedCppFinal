#ifndef DATECONVERSION_HPP
#define DATECONVERSION_HPP
/*
#include <iostream>
#include <sstream>
#include <locale>
#include "boost/date_time/gregorian/greg_date.hpp"

static const std::locale fmt(std::locale::classic(),new boost::gregorian::date_facet("%m/%d/%Y"));
const std::locale fmt2(std::locale::classic(),
	new boost::gregorian::date_input_facet("%m/%d/%Y"));

std::string dateAsMMDDYYYY(const boost::gregorian::date& date)
{
	std::ostringstream os;
	os.imbue(fmt);
	os << date;
	return os.str();
}

boost::gregorian::date MMDDYYYYasDate(const std::string& str)
{
	std::istringstream is(str);
	is.imbue(fmt2);
	boost::gregorian::date date;
	is >> date;
	return date;
}
*/
#endif