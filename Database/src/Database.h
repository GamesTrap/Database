#pragma once

#include "Record.h"
#include <vector>

class Database
{
public:
	void addRecord(unsigned int id, std::string Firstname, std::string Lastname);
	bool removeRecord(unsigned int index);

	bool checkRecordIndex(unsigned int index) const;

	Record getRecordByIndex(unsigned int index);
	unsigned int getNextId() const;
	unsigned int getRecordsSize() const;
	std::string getName(unsigned int Index, bool isFirstname);
	void setId(unsigned int index);

private:
	std::vector<Record> m_records;
};