#pragma once
#include "Database.h"

class Menu : Database
{
public:
	Menu();
	explicit Menu(Database &database);

	void displayMenu();

private:
	Database m_database;
};
