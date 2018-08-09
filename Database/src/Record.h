#pragma once

#include <string>

struct Record
{
	Record();
	Record(unsigned int id, std::string firstname, std::string lastname);

	//Values
	unsigned int ID;

	std::string Firstname;
	std::string Lastname;
};
