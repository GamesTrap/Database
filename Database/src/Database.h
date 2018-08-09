#pragma once

#include "Record.h"
#include <vector>

class Database
{
public:
	void addRecord(std::string Firstname, std::string Lastname);

	bool checkRecordIndex(unsigned int index) const;

	Record getRecordByIndex(unsigned int index);
	unsigned int getNextId() const;
	unsigned int getRecordsSize() const;
	std::string getName(unsigned int Index, bool isFirstname);

private:
	std::vector<Record> m_records;
};