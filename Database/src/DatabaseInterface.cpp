#include <iostream>
#include "DatabaseInterface.h"
#include <cctype>

DatabaseInterface::DatabaseInterface()
{
	displayMenu();
}

void DatabaseInterface::displayMenu()
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
			addRecord();
			break;
		case 2: //ShowByID
			clearScreen();
			//showRecordById();
			continueScreen();
			break;
		case 3: //ShowAll
			clearScreen();
			//showAllRecords();
			continueScreen();
			break;
		case 4: //UpdateRecordByID
			//displayUpdateMenu();
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

/*void DatabaseInterface::displayUpdateMenu()
{
	int menu;
	std::string menuStr;
	TextTable table;

	//save table to string or 
	if(!getRecordAndTable(table))
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
}*/

void DatabaseInterface::addRecord()
{
	std::cout << "Database ID: " << getNextId() << '\n' << '\n';

	std::cout << "Please enter firstname: ";
	const std::string firstname = getName();
	std::cout << '\n';

	std::cout << "Please enter lastname: ";
	const std::string lastname = getName();

	Database::addRecord(firstname, lastname);
}

std::string DatabaseInterface::getName() const
{
	std::string temp;

	std::cin.clear();
	std::getline(std::cin, temp);

	validateName(temp);

	return temp;
}

void DatabaseInterface::validateName(std::string& name) const
{
	bool isCorrect = false; //Default Wrong Input

	do
	{
		if (name.empty())
			isCorrect = false; //Wrong Input
		else if (name.at(0) == ' ')
			isCorrect = false; //Wrong Input
		else if (name.at(name.size() - 1) == ' ')
			isCorrect = false; //Wront Input
		else
		{
			for (auto& i : name)
			{
				if (!std::isalpha(i) || std::isdigit(i))
					isCorrect = !std::isspace(i) == 0; //Default Wrong Input except if i is ' '
				else if (std::isalpha(i))
					//Correct input
					isCorrect = true;

				if (!isCorrect)
					break; //Wrong Input
			}
		}

		if (!isCorrect) //Handle Wrong Input
		{
			std::cout << '\n' << "Wrong Input!" << '\n' << "Please try again: ";
			std::cin.clear();
			std::getline(std::cin, name);
		}

	} while (!isCorrect);
}

void DatabaseInterface::clearScreen()
{
	std::cout << std::string(100, '\n');
}
void DatabaseInterface::continueScreen()
{
	std::cout << "Press Enter to continue . . . ";
	std::cin.get();
}
bool DatabaseInterface::confirmScreen() const
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