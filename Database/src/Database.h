#pragma once

#include "Record.h"
#include <vector>
#include "TextTable.h"

class Database
{
public:
	void showRecordById();
	void showAllRecords();

	void addRecord();
	void addRecordToTableById(std::size_t id);
	void addRecordToTable(Record &record);

	bool getRecordAndTable(TextTable &table);

private:
	std::size_t getNextId() const;
	std::size_t getId() const;
	std::size_t getAllRecords() const;
	std::string getName(bool firstname) const;
	std::string getNameById(std::size_t id, bool firstname);
	Record getRecord(std::size_t id);

	void checkName(std::string &name) const;
	bool checkId(std::size_t &id) const;

	void initTable();

	std::vector<Record> m_records;
	TextTable m_table;
};