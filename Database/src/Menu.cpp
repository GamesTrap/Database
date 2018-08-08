#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	displayMenu();
}

Menu::Menu(Database& database)
	: m_database{database}
{
	displayMenu();
}

void Menu::displayMenu()
{
	int menu;
	std::string menuStr;

	while (true)
	{
		std::cout << "1 - Add Record" << '\n'
			<< "2 - Show Record by ID" << '\n'
			<< "3 - Show all Records" << '\n'
			<< "4 - Quit" << '\n'
			<< "Enter a number and press return: ";

		std::getline(std::cin, menuStr);
		try
		{
			menu = std::stoi(menuStr);
		}
		catch (...)
		{
			menu = -1;
		}

		switch (menu)
		{
		case 1: //Add
			m_database.addRecord();
			break;
		case 2: //ShowByID
			m_database.showRecordById();
			break;
		case 3: //ShowAll
			m_database.showAllRecords();
			break;
		case 4:
			std::cout << '\n' << "Press any key to continue . . . ";
			std::cin.get();
			exit(0);

		default:
			std::cout << '\n' << "Invalid input." << '\n'
				<< "Please try again" << '\n' << '\n';
		}
	}
}