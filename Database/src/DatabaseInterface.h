#pragma once

#include "Database.h"
#include "TextTable.h"

class DatabaseInterface : public Database
{
public:
	//Constructor
	DatabaseInterface();

	//Menus
	void displayMenu();
	void displayUpdateMenu();
	void displayShowMenu();
	void displaySettingsMenu() const;

private:
	//Functions
	void addRecordFromUser();
	void removeRecordFromUser(int index);
	void showRecordByIndexFromUser();
	void showAllRecords();
	void updateFirstname(int index);
	void updateLastname(int index);

	//Getters
	std::string getNameFromUser() const;
	int getIndexFromUser() const;
	bool getTableWithRecord(TextTable& table, int index);

	//Validators
	void validateName(std::string& name) const;
	void validateIndex(int& index) const;

	//Table Functions
	void initializeTable();
	void clearTable();
	void addRecordToTableByRecord(Record& record);
	void addRecordToTableByIndex(unsigned int index);

	//Utility Functions
	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;

	TextTable m_table;
};
