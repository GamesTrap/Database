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
		clearScreen();

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
			clearScreen();
			m_database.addRecord();
			break;
		case 2: //ShowByID
			clearScreen();
			m_database.showRecordById();
			continueScreen();
			break;
		case 3: //ShowAll
			clearScreen();
			m_database.showAllRecords();
			continueScreen();
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

void Menu::clearScreen()
{
	std::cout << std::string(100, '\n');
}

void Menu::continueScreen()
{
	std::cout << "Press any key to continue . . . ";
	std::cin.get();
}