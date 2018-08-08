#pragma once
#include "Database.h"

class Menu 
{
public:
	Menu();
	explicit Menu(Database &database);

	void displayMenu();
	void displayUpdateMenu();

private:
	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;

	Database m_database;
};