#pragma once

#include "Record.h"
#include <vector>
#include "TextTable.h"

class Database
{
public:
	void addRecord();
	void showRecordById();
	void showAllRecords();

	void displayMenu();

	static void addRecordToTable(const Record &record, TextTable& table);

private:
	unsigned int getNextId() const;
	unsigned int getId();
	std::size_t  getAllRecords() const;
	std::string getName(bool firstname) const;
	std::string getNameById(int id, bool firstname);

	void checkName(std::string &name) const;
	bool checkId(int &id) const;

	std::vector<Record> m_records;
	TextTable m_table;
};