#pragma once

#include "Database.h"

class DatabaseInterface : public Database
{
public:
	DatabaseInterface();

	void displayMenu();
	//void displayUpdateMenu();

private:
	void addRecord();
	void showRecordByIndex();

	std::string getName() const;
	std::size_t getIndex() const;

	void validateName(std::string& name) const;
	void validateIndex(std::size_t &index) const;

	void initTable();
	void addRecordToTableByIndex(std::size_t index);

	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;

	TextTable m_table;
};