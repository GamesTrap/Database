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
		          << "4 - Update Record by ID" << '\n'
			      << "5 - Quit" << '\n'
			      << "Enter a number and press enter: ";

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
		case 4: //UpdateRecordByID
			displayUpdateMenu();
			break;
		case 5: //Close Database
		{
			const bool close = confirmScreen();
			if (close)
				exit(0);
			break;
		}

		default: 
			;
		}
	}
}

void Menu::displayUpdateMenu()
{
	int menu;
	std::string menuStr;
	TextTable table;

	//save table to string or 
	if(!m_database.getRecordAndTable(table))
		return;

	while (true)
	{
		clearScreen();

		std::cout << '\n' << table << '\n' << '\n';

		std::cout << "1 - Change ID" << '\n'
			      << "2 - Change Firstname" << '\n'
			      << "3 - Change Lastname" << '\n'
		          << "4 - Go back to main menu" << '\n'
			      << "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		try
		{
			menu = std::stoi(menuStr);
		}
		catch(...)
		{
			menu = -1;
		}

		switch(menu)
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			return;

		default:
			;
		}
	}
}

void Menu::clearScreen()
{
	std::cout << std::string(100, '\n');
}
void Menu::continueScreen()
{
	std::cout << "Press Enter to continue . . . ";
	std::cin.get();
}
bool Menu::confirmScreen() const
{
	std::string confirm;
	while(true)
	{		
	    std::cout << '\n' << "Are you sure (yes/no): ";
		std::getline(std::cin, confirm);

		//returns true if confirm == yes or YES or y or Y else returns false
		return (!confirm.empty() && confirm == "yes") || (!confirm.empty() && confirm == "YES") || (!confirm.empty() && confirm == "y") || (!confirm.empty() && confirm == "Y");
	}
}