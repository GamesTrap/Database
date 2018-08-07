#include "Record.h"

Record::Record(unsigned int id, std::string firstname, std::string lastname)
	: m_id{ id }, m_firstname{ std::move(firstname) }, m_lastname{ std::move(lastname) }
{}

Record::Record()
	: m_id(0), m_firstname{""}, m_lastname{""}
{}