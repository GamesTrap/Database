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
		if (menuStr.length() > 1)
			menu = -1;
		else
		{
			try
			{
				menu = std::stoi(menuStr);
			}
			catch (...)
			{
				menu = -1;
			}
		}		

		switch (menu)
		{
		case 1: //Add
			addRecordFromUser();
			break;
		case 2: //Show single Record
			showRecordByIndexFromUser();
			break;
		case 3: //Show all Records
			showAllRecords();
			break;
		case 4: //Update single Record
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

void DatabaseInterface::displayUpdateMenu()
{
	int menu;
	std::string menuStr;

	clearScreen();
	std::cout << "Please enter a Database ID: ";
	const int index = getIndexFromUser();

	while (true)
	{
		if (!getTableWithRecord(m_table, index))
			return;

		clearScreen();

		std::cout << '\n' << m_table << '\n';

		std::cout << "1 - Change ID" << '\n'
			      << "2 - Change Firstname" << '\n'
			      << "3 - Change Lastname" << '\n'
		          << "4 - Delete Record" << '\n'
		          << "5 - Go back to main menu" << '\n'
			      << "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menu = -1;
		else
		{
			try
			{
				menu = std::stoi(menuStr);
			}
			catch (...)
			{
				menu = -1;
			}
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
			removeRecordFromUser(index);
			break;
		case 5:
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::addRecordFromUser()
{
	clearScreen();

	int id = getNextId();

	std::cout << "Database ID: " << id << '\n' << '\n';

	std::cout << "Please enter firstname: ";
	const std::string firstname = getNameFromUser();
	std::cout << '\n';

	std::cout << "Please enter lastname: ";
	const std::string lastname = getNameFromUser();

	addRecord(id, firstname, lastname);
}
void DatabaseInterface::removeRecordFromUser(const int index)
{
	if (!confirmScreen())
		return;

	clearScreen();	

	if(index == -1)
	{
		std::cout << '\n';
		return;
	}

	removeRecord(index);

	std::cout << "Database Record deleted!" << '\n';

	continueScreen();

	displayMenu();
}
void DatabaseInterface::showRecordByIndexFromUser()
{
	clearScreen();

	std::cout << "Please enter a Database ID: ";
	const int index = getIndexFromUser();

	if(index == -1)
	{
		std::cout << '\n';
		return;
	}

	clearScreen();

	auto record = getRecordByIndex(index);

	clearTable();
	initializeTable();
	addRecordToTableByRecord(record);

	std::cout << '\n' << m_table << '\n';

	continueScreen();
}
void DatabaseInterface::showAllRecords()
{
	clearScreen();

	const std::size_t recordsSize = getRecordsSize();

	if (recordsSize == 0)
	{
		std::cout << "Records: " << recordsSize << '\n' << '\n';
		continueScreen();
		return;
	}

	std::cout << "Records: " << recordsSize << '\n';

	clearTable();
	initializeTable();

	for(std::size_t i = 0; i < recordsSize; i++)
	{
		addRecordToTableByIndex(i);
	}

	std::cout << '\n' << m_table << '\n';

	continueScreen();
}

std::string DatabaseInterface::getNameFromUser() const
{
	std::string temp;

	std::cin.clear();
	std::getline(std::cin, temp);

	validateName(temp);

	return temp;
}
int DatabaseInterface::getIndexFromUser() const
{
	std::string idStr;
	int index;

	std::getline(std::cin, idStr);
	if (idStr.length() > 1)
		index = -1;
	else
	{
		try
		{
			index = std::stoi(idStr);
		}
		catch (...)
		{
			index = -1;
		}
	}

	validateIndex(index);

	return index;
}

bool DatabaseInterface::getTableWithRecord(TextTable& table, const int index)
{
	if(index == -1)
	{
		std::cout << '\n';
		return false;
	}

	clearTable();
	initializeTable();
	addRecordToTableByIndex(index);

	return true;
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
					isCorrect = std::isspace(i) != 0; //If i is ' ' return true else false
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

void DatabaseInterface::validateIndex(int& index) const
{
	std::string temp;

	while(!checkRecordIndex(index))
	{
		std::cout << '\n' << "Invalid Input." << '\n'
			<< "Please try again or press 'x' to cancel: ";
		std::getline(std::cin, temp);

		if (temp == "x" || temp == "X")
		{
			index = -1;
			break;
		}

		try
		{
			index = std::stoi(temp);
		}
		catch (...)
		{
		}
	}
}

void DatabaseInterface::initializeTable()
{
	m_table.add("ID");
	m_table.add("Firstname");
	m_table.add("Lastname");
	m_table.endOfRow();
}
void DatabaseInterface::clearTable()
{
	m_table.clearTextTable();
}
void DatabaseInterface::addRecordToTableByRecord(Record &record)
{
	m_table.add(std::to_string(record.ID));
	m_table.add(record.Firstname);
	m_table.add(record.Lastname);
	m_table.endOfRow();
}
void DatabaseInterface::addRecordToTableByIndex(const unsigned int index)
{
	const auto temp = getRecordByIndex(index);

	m_table.add(std::to_string(temp.ID));
	m_table.add(temp.Firstname);
	m_table.add(temp.Lastname);
	m_table.endOfRow();
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