#pragma once

#include <string>

class Record
{
public:
	Record(unsigned int id, std::string firstname, std::string lastname);
	Record();

	unsigned int m_id;

	std::string m_firstname;
	std::string m_lastname;
};