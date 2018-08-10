#pragma once

#include <string>

struct Record
{
	//Constructors
	Record();
	Record(unsigned int id, std::string firstname, std::string lastname);

	//Variables
	unsigned int ID;
	std::string Firstname;
	std::string Lastname;
};