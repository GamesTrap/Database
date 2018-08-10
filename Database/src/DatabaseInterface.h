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
	void displayImportMenu();

private:
	//Functions
	void addRecordFromUser();
	void removeRecordFromUser(int index);
	void showRecordByIndexFromUser();
	void showAllRecords();
	void updateName(int index, bool isFirstname);
	void exportDatabaseToFile();
	void importFileToDatabase();
	bool databaseIsEmpty() const;
	void clearDatabase();

	//Utility Functions
	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;

	//Getters
	std::string getNameFromUser() const;
	int getIndexFromUser() const;
	bool getTableWithRecord(TextTable& table, int index);
	void getNumberOfRecords() const;
	std::string getFilenameFromUser() const;

	//Table Functions
	void initializeTable();
	void clearTable();
	void addRecordToTableByRecord(Record& record);
	void addRecordToTableByIndex(unsigned int index);
	void exportTableToFile() const;

	TextTable m_table;
};