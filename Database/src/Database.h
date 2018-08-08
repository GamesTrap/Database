#pragma once

#include "TextTable.h"
#include "RecordsManager.h"

class Database : public RecordsManager
{
public:
	//Adds a Record to m_records
	void addRecord(const std::string& Firstname, const std::string& Lastname);

private:

	TextTable m_table;
};
