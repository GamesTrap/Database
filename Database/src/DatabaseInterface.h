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

	std::string getName() const;

	void validateName(std::string& name) const;

	static void clearScreen();
	static void continueScreen();
	bool confirmScreen() const;
};