#include <iostream>
#include "Database.h"

int main()
{
	Database database;
	database.displayMenu();

	std::cout << "Press any key to continue . . . ";
	//std::cin.ignore(1000, '\n');
	std::cin.get();
	return 0;
}
