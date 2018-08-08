#include "Database.h"

#include <iostream>
#include <cctype>
#include <string>

void Database::addRecord()
{	
	const int id = getNextId();
	const std::string firstname = getName(true);
	const std::string lastname = getName(false);

	m_records.emplace_back(id, firstname, lastname);
}

void Database::showRecordById()
{
	const std::size_t id = getId();
	if (id == -1)
		return;

	initTable();
	addRecordToTableById(id);

	std::cout << '\n' << m_table << '\n';
}

void Database::showAllRecords()
{
	std::cout << '\n' << "Number of Records: " << getAllRecords() << '\n' << '\n';

	initTable();	

	for(auto& i : m_records)
	{
		addRecordToTable(i);
	}

	std::cout << m_table << '\n';
}



void Database::addRecordToTableById(const std::size_t id)
{
	m_table.add(std::to_string(m_records.at(id).m_id));
	m_table.add(m_records.at(id).m_firstname);
	m_table.add(m_records.at(id).m_lastname);
	m_table.endOfRow();
}

void Database::addRecordToTable(Record& record)
{
	m_table.add(std::to_string(record.m_id));
	m_table.add(record.m_firstname);
	m_table.add(record.m_lastname);
	m_table.endOfRow();
}

std::size_t Database::getNextId() const
{
	const auto id = static_cast<unsigned int>(m_records.size());
	std::cout << '\n' << "Database ID: " << id << '\n';

	return id;
}

std::size_t Database::getId() const
{
	std::string idStr;
	std::size_t id;
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
		id = -1;

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

std::string Database::getNameById(const std::size_t id, const bool firstname)
{
	if (firstname)
		return m_records.at(id).m_firstname;
	else
		return m_records.at(id).m_lastname;
}

Record Database::getRecord(std::size_t id)
{
	if (!checkId(id))
		id = -1;

	return m_records.at(id);
}

void Database::checkName(std::string &name) const
{
	bool wrong = false; //Default Correct Input

	do
	{	
		if(name.empty())
			wrong = true; //Wrong Input
		else if (name.at(0) == ' ')
			wrong = true; //Wrong Input
		else if (name.at(name.size() - 1) == ' ')
			wrong = true; //Wront Input
		else
		{
			for (auto& i : name)
			{
				if (!std::isalpha(i) || std::isdigit(i))
					wrong = std::isspace(i) == 0; //Default Wrong Input except if i is ' '
				else if(std::isalpha(i))
					//Correct input
					wrong = false;

				if (wrong)
					break; //Wrong Input
			}
		}

		if (wrong) //Handle Wrong Input
		{
			std::cout << '\n' << "Wrong Input!" << '\n' << "Please try again: ";
			std::cin.clear();
			std::getline(std::cin, name);
		}

	} while (wrong);
}

bool Database::checkId(std::size_t &id) const
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

void Database::initTable()
{
	m_table.clear();

	m_table.add("ID");
	m_table.add("Firstname");
	m_table.add("Lastname");
	m_table.endOfRow();
}