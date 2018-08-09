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
	void displaySettingsMenu();
	void displayExportMenu();

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
	void getNumberOfRecords() const;
	std::string getFilenameFromUser() const;

	//Validators
	void validateName(std::string& name) const;
	void validateIndex(int& index) const;
	void validateFilename(std::string& filename) const;

	//Table Functions
	void initializeTable();
	void clearTable();
	void addRecordToTableByRecord(Record& record);
	void addRecordToTableByIndex(unsigned int index);
	void exportTableToFile() const;

	//Utility Functions
	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;

	TextTable m_table;
};