#pragma once

#include <string>

struct Record
{
	Record();
	Record(std::size_t id, std::string firstname, std::string lastname);

	//Values
	std::size_t ID;

	std::string Firstname;
	std::string Lastname;
};