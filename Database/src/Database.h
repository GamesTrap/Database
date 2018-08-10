#pragma once

#include "Record.h"
#include <vector>

class Database
{
public:
	void addRecord(unsigned int id, std::string Firstname, std::string Lastname);
	bool removeRecord(unsigned int index);

	Record getRecordByIndex(unsigned int index);
	unsigned int getNextId() const;

	void setFirstname(unsigned int index, const std::string& Firstname);
	void setLastname(unsigned int index, const std::string& Lastname);

	bool checkRecordIndex(unsigned int index) const;

	std::string toString();

	bool importOverwrite(std::vector<std::string> &CSVs, unsigned int lines);

	void clearRecords();

private:
	std::string getName(unsigned int Index, bool isFirstname);
	void setId(unsigned int index);

	std::vector<Record> m_records;
};
