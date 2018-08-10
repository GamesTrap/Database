#include "Record.h"

//Constructors
Record::Record()
	: ID(0), Firstname{""}, Lastname{""} {}

Record::Record(const unsigned int id, std::string firstname, std::string lastname)
	: ID{id}, Firstname{std::move(firstname)}, Lastname{std::move(lastname)} {}