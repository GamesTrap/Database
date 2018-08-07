#pragma once

#include "Record.h"
#include <vector>

class Database
{
public:
	void addRecord();
	void showRecordById();

	void displayMenu();

protected:
	int getNextId() const;
	int getId();
	std::string getName(bool firstname) const;
	std::string getNameById(int id, bool firstname);

private:
	void checkName(std::string &name) const;
	bool checkId(int &id) const;

	std::vector<Record> m_records;
};