#include "DatabaseInterface.h"

#include <iostream>
#include <cctype>
#include <fstream>

DatabaseInterface::DatabaseInterface() { displayMenu(); }

void DatabaseInterface::displayMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "1 - Add Record" << '\n'
				<< "2 - Show Record(s)" << '\n'
				<< "3 - Update Record" << '\n'
				<< "4 - Settings" << '\n'
				<< "5 - Quit" << '\n'
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case '1':
			addRecordFromUser();
			break;
		case '2':
			displayShowMenu();
			break;
		case '3':
			displayUpdateMenu();
			break;
		case '4':
			displaySettingsMenu();
			break;
		case 'x':
			[[fallthrough]];
		case '5':
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

		std::cout << "1 - Change Firstname" << '\n'
				<< "2 - Change Lastname" << '\n'
				<< "3 - Delete Record" << '\n'
				<< "4 - Main Menu" << '\n'
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case '1':
			updateFirstname(index);
			break;
		case '2':
			updateLastname(index);
			break;
		case '3':
			removeRecordFromUser(index);
			break;
		case 'x':
			[[fallthrough]];
		case '4':
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::displayShowMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "1 - All" << '\n'
				<< "2 - By ID" << '\n'
				<< "3 - Main Menu" << '\n'
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case '1':
			clearScreen();
			getNumberOfRecords();
			showAllRecords();
			continueScreen();
			break;
		case '2':
			showRecordByIndexFromUser();
			break;
		case 'x':
			[[fallthrough]];
		case '3':
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::displaySettingsMenu()
{
	int menu;
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "1 - Export" << '\n'
			<< "2 - Import" << '\n'
		    << "3 - Clear Database" << '\n'
			<< "4 - Main Menu" << '\n'
			<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menu = -1;
		else if (menuStr == "x" || menuStr == "X")
			return;
		else
		{
			try { menu = std::stoi(menuStr); }
			catch (...) { menu = -1; }
		}

		switch (menu)
		{
		case 1:
			if(getNextId() > 0)
			    displayExportMenu();
			else
			{
				clearScreen();
				std::cout << '\n' << "Database is empty!" << '\n' << '\n';
				continueScreen();				
			}
			break;
		case 2:
			if (getNextId() > 0)
				displayImportMenu();
			else
			{
				if (!confirmScreen())
					return;
				clearScreen();
				importFileToDatabase();
				continueScreen();
			}
			break;
		case 3:
			if(!confirmScreen())
				break;

			clearRecords();
			break;
		case 'x':
			[[fallthrough]];
		case 4:
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::displayExportMenu()
{
	int menu;
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "1 - Export Table" << '\n'
			      << "2 - Export Database" << '\n'
			      << "3 - Main Menu" << '\n'
			      << "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menu = -1;
		else if (menuStr == "x" || menuStr == "X")
			return;
		else
		{
			try { menu = std::stoi(menuStr); }
			catch (...) { menu = -1; }
		}

		switch (menu)
		{
		case 1:
			clearScreen();
			showAllRecords();
			exportTableToFile();
			continueScreen();
			break;
		case 2:
			clearScreen();
			exportDatabaseToFile();
			continueScreen();
			break;
		case 'x':
			[[fallthrough]];
		case 3:
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::displayImportMenu()
{
	int menu;
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "1 - Overwrite All" << '\n'
			<< "2 - Add to existing" << '\n'
			<< "3 - Main Menu" << '\n'
			<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menu = -1;
		else if (menuStr == "x" || menuStr == "X")
			return;
		else
		{
			try { menu = std::stoi(menuStr); }
			catch (...) { menu = -1; }
		}

		switch (menu)
		{
		case 1:
			if (!confirmScreen())
				break;

			clearScreen();
			clearRecords();
			importFileToDatabase();
			continueScreen();
			break;
		case 2:
			if (!confirmScreen())
				break;

			clearScreen();
			importFileToDatabase();
			continueScreen();
			break;
		case 'x':
			[[fallthrough]];
		case 3:
			return;

		default:
			;
		}
	}
}

void DatabaseInterface::addRecordFromUser()
{
	clearScreen();

	const int id = getNextId();

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

	if (index == -1)
	{
		std::cout << '\n';
		return;
	}

	removeRecord(index);

	std::cout << "Database Record deleted!" << '\n' << '\n';

	continueScreen();

	displayMenu();
}

void DatabaseInterface::showRecordByIndexFromUser()
{
	clearScreen();

	std::cout << "Please enter a Database ID: ";
	const int index = getIndexFromUser();

	if (index == -1)
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
	clearTable();
	initializeTable();

	for (unsigned int i = 0; i < getNextId(); i++) { addRecordToTableByIndex(i); }

	std::cout << '\n' << m_table << '\n';
}

void DatabaseInterface::updateFirstname(const int index)
{
	clearScreen();

	std::cout << m_table << '\n';

	std::cout << "Please enter firstname: ";
	const std::string firstname{getNameFromUser()};

	setFirstname(index, firstname);
}

void DatabaseInterface::updateLastname(const int index)
{
	clearScreen();

	std::cout << m_table << '\n';

	std::cout << "Please enter lastname: ";
	const std::string lastname{getNameFromUser()};

	setLastname(index, lastname);
}

void DatabaseInterface::exportDatabaseToFile()
{
	std::cout << "Please enter a filename: ";

	std::string filename(getFilenameFromUser());
	if (filename.find(".csv") == std::string::npos && filename.find(".db") == std::string::npos)
		filename += ".csv";

	std::ofstream output(filename);

	if (!output)
	{
		std::cerr << '\n' << filename << " could not be opened for writing!" << '\n' << std::endl;
		return;
	}

	output << toString();

	output.close();

	std::cout << '\n' << "Successfully exported Database!" << '\n' << '\n';
}

void DatabaseInterface::importFileToDatabase()
{
	std::string temp;
	std::vector<std::string> CSVs;
	unsigned int elements = 0;

	std::cout << "Please enter a filename: ";

	std::string filename(getFilenameFromUser());
	if (filename.find(".csv") == std::string::npos && filename.find(".db") == std::string::npos)
		filename += ".csv";

	std::ifstream input(filename);

	if(!input)
	{
		std::cerr << '\n' << filename << " could not be opened for reading!" << '\n' << std::endl;
		return;
	}

	while(input)
	{
		std::getline(input, temp, ',');
		if (temp.at(temp.length() - 1) == '\n')
			temp.pop_back();

		CSVs.push_back(temp);
		elements++;
	}
	elements--;

	if (!importDatabase(CSVs, elements))
		std::cout << '\n' << "An error has occured!" << '\n' << '\n';
	else
	{
		showAllRecords();
		std::cout << "Successfully imported Database!" << '\n' << '\n';		
	}
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
		try { index = std::stoi(idStr); }
		catch (...) { index = -1; }
	}

	validateIndex(index);

	return index;
}

bool DatabaseInterface::getTableWithRecord(TextTable& table, const int index)
{
	if (index == -1)
	{
		std::cout << '\n';
		return false;
	}

	clearTable();
	initializeTable();
	addRecordToTableByIndex(index);

	return true;
}

void DatabaseInterface::getNumberOfRecords() const
{
	const std::size_t recordsSize = getNextId();

	if (recordsSize == 0)
	{
		std::cout << "Records: " << recordsSize << '\n' << '\n';
		continueScreen();
		return;
	}

	std::cout << "Records: " << recordsSize << '\n';
}

std::string DatabaseInterface::getFilenameFromUser() const
{
	std::string filename;

	std::cin.clear();
	std::getline(std::cin, filename);

	validateFilename(filename);

	return filename;
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
	}
	while (!isCorrect);
}

void DatabaseInterface::validateIndex(int& index) const
{
	std::string temp;

	while (!checkRecordIndex(index))
	{
		std::cout << '\n' << "Invalid Input." << '\n'
				<< "Please try again or press 'x' to cancel: ";
		std::getline(std::cin, temp);

		if (temp == "x" || temp == "X")
		{
			index = -1;
			break;
		}

		try { index = std::stoi(temp); }
		catch (...) { }
	}
}

void DatabaseInterface::validateFilename(std::string& filename) const
{
	bool isCorrect = false;

	do
	{
		if (filename.empty())
			isCorrect = false; //Wrong Input
		else if (filename.at(0) == ' ')
			isCorrect = false; //Wrong Input
		else if (filename.at(filename.size() - 1) == ' ')
			isCorrect = false; //Wront Input
		else
		{
			isCorrect = true;
		}

		if (!isCorrect) //Handle Wrong Input
		{
			std::cout << '\n' << "Wrong Input!" << '\n' << "Please try again: ";
			std::cin.clear();
			std::getline(std::cin, filename);
		}
	} while (!isCorrect);
}

void DatabaseInterface::initializeTable()
{
	m_table.add("ID");
	m_table.add("Firstname");
	m_table.add("Lastname");
	m_table.endOfRow();
}

void DatabaseInterface::clearTable() { m_table.clearTextTable(); }

void DatabaseInterface::addRecordToTableByRecord(Record& record)
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

void DatabaseInterface::exportTableToFile() const
{
	std::cout << "Please enter a filename: ";

	std::string filename(getFilenameFromUser());
	if (filename.find(".txt") == std::string::npos)
		filename += ".txt";

	std::ofstream output(filename);

	if(!output)
	{
		std::cerr << filename << " could not be opened for writing!" << std::endl;
		return;
	}

	output << m_table;

	output.close();

	std::cout << '\n' << "Successfully exported Table!" << '\n' << '\n';
}

void DatabaseInterface::clearScreen() { std::cout << std::string(100, '\n'); }

void DatabaseInterface::continueScreen()
{
	std::cout << "Press Enter to continue . . . ";
	std::cin.get();
}

bool DatabaseInterface::confirmScreen() const
{
	std::string confirm;
	while (true)
	{
		std::cout << '\n' << "Are you sure (yes/no): ";
		std::getline(std::cin, confirm);

		//returns true if confirm == yes or YES or y or Y else returns false
		return (!confirm.empty() && confirm == "yes") || (!confirm.empty() && confirm == "YES") || (!confirm.empty() &&
			confirm == "y") || (!confirm.empty() && confirm == "Y");
	}
}
