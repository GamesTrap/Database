#include "Database.h"

#include <iostream>
#include <cctype>

void Database::addRecord()
{	
	const int id = getNextId();
	const std::string firstname = getName(true);
	const std::string lastname = getName(false);

	m_records.emplace_back(id, firstname, lastname);
}

void Database::showRecordById()
{
	const int id = getId();

	std::cout << '\n' << "ID: " << id << '\n'
	          << "Firstname: " <<  getNameById(id, true) << '\n' 
	          << "Lastname: " << getNameById(id, false) << '\n' << '\n';
}

void Database::showAllRecords()
{
	std::cout << '\n' << "Number of Records: " << getAllRecords() << '\n' << '\n';

	TextTable table('-', '|', '+');
	table.add("ID");
	table.add("Firstname");
	table.add("Lastname");
	table.endOfRow();

	for(const auto& i : m_records)
	{
		addRecordToTable(i, table);
	}

	std::cout << table << '\n';
}

void Database::displayMenu()
{
	int menu;
	std::string menuStr;

	while(true)
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
		catch(...)
		{
			menu = -1;
		}

		switch(menu)
		{
		case 1: //Add
			addRecord();
			break;
		case 2:
			showRecordById();
			break;
		case 3:
			showAllRecords();
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

void Database::addRecordToTable(const Record &record, TextTable& table)
{
	//std::cout << "ID: " << record.m_id << " Firstname: " << record.m_firstname << " Lastname: " << record.m_lastname << '\n' << '\n';
	table.add(std::to_string(record.m_id));
	table.add(record.m_firstname);
	table.add(record.m_lastname);
	table.endOfRow();
}

unsigned int Database::getNextId() const
{
	const auto id = static_cast<unsigned int>(m_records.size());
	std::cout << '\n' << "Database ID: " << id << '\n';

	return id;
}

unsigned int Database::getId()
{
	std::string idStr;
	int id;
	std::cout << '\n' << "Please enter a Database ID: ";
	std::getline(std::cin, idStr);
	try
	{
		id = std::stoi(idStr);
	}
	catch(...)
	{
		id = -1;
	}

	if (!checkId(id))
	{
		std::cout << '\n';
		displayMenu();
	}

	return id;
}

std::size_t Database::getAllRecords() const
{
	return m_records.size();
}

std::string Database::getName(const bool firstname) const
{
	std::string name;

	if(firstname) //Firstname
	{
		std::cout << '\n' << "Please enter firstname: ";
		std::cin.clear();
		std::getline(std::cin, name);

		checkName(name);
	}
	else //Lastname
	{
		std::cout << '\n' << "Please enter lastname: ";
		std::cin.clear();
		std::getline(std::cin, name);

		checkName(name);

		std::cout << '\n';
	}

	return name;
}

std::string Database::getNameById(const int id, const bool firstname)
{
	if (firstname)
		return m_records.at(id).m_firstname;
	else
		return m_records.at(id).m_lastname;
}

void Database::checkName(std::string &name) const
{
	do
	{
		for(auto& i : name)
		{
			if(!(std::isalpha(i) || (std::isspace(i) && name.find_first_of(' '))))
			{
				std::cout << "Wrong Input!" << '\n' << "Please try again: ";
				std::cin.clear();
				std::getline(std::cin, name);
			}
			else //Correct input
				return;
		}
	} while (true);
}

bool Database::checkId(int &id) const
{
	std::string temp;

	while (m_records.size() <= id)
	{
		std::cout << '\n' << "Invalid input." << '\n'
			      << "Please try again or Press 'x' to exit: ";
		std::getline(std::cin, temp);

		if (temp == "x" || temp == "X")
			return false;

		try
		{
			id = std::stoi(temp);
		}
		catch(...)
		{}
	}
	return true;
}