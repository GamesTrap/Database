#pragma once
#include "Database.h"

class Menu : Database
{
public:
	Menu();
	explicit Menu(Database &database);

	void displayMenu();


private:
	static void clearScreen();
	static void continueScreen();

	Database m_database;
};
