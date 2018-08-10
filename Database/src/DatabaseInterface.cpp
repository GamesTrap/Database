#include "DatabaseInterface.h"

#include <iostream>
#include <fstream>

//Constructor
DatabaseInterface::DatabaseInterface() { displayMenu(); }

//Menus
void DatabaseInterface::displayMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "0 - Quit" << '\n'
		        << "1 - Add Record" << '\n'
				<< "2 - Show Record(s)" << '\n'
				<< "3 - Update Record" << '\n'
				<< "4 - Settings" << '\n'				
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
		{
			const bool close = confirmScreen();
			if (close)
				exit(0);
			break;
		}
		case '1':
			addRecordFromUser();
			break;
		case '2':
			if(!databaseIsEmpty())
				displayShowMenu();
			break;
		case '3':
			displayUpdateMenu();
			break;
		case '4':
			displaySettingsMenu();
			break;		

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

	if (index == -1)
		return;

	while (true)
	{
		if (!getTableWithRecord(m_table, index))
			return;

		clearScreen();

		std::cout << '\n' << m_table << '\n';

		std::cout << "0 - Main Menu" << '\n'
		        << "1 - Change Firstname" << '\n'
				<< "2 - Change Lastname" << '\n'
				<< "3 - Delete Record" << '\n'				
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
			return;
		case '1':
			updateFirstname(index);
			break;
		case '2':
			updateLastname(index);
			break;
		case '3':
			removeRecordFromUser(index);
			break;		

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

		std::cout << "0 - Main Menu" << '\n'
		        << "1 - All" << '\n'
				<< "2 - By ID" << '\n'				
				<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
			return;
		case '1':
			clearScreen();
			getNumberOfRecords();
			showAllRecords();
			continueScreen();
			break;
		case '2':
			showRecordByIndexFromUser();
			break;		

		default:
			;
		}
	}
}
void DatabaseInterface::displaySettingsMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "0 - Main Menu" << '\n'
			<< "1 - Export" << '\n'
			<< "2 - Import" << '\n'
		    << "3 - Clear Database" << '\n'
			<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
			return;
		case '1':
			if (!databaseIsEmpty())
				displayExportMenu();
			break;
		case '2':
			if (!isDatabaseEmpty())
				displayImportMenu();
			else
			{
				if (!confirmScreen())
					break;
				clearScreen();
				importFileToDatabase();
				continueScreen();
			}
			break;
		case '3':
			if (databaseIsEmpty())
				break;
			if (!confirmScreen())
				break;
			clearDatabase();
			continueScreen();
			break;

		default:
			;
		}
	}
}
void DatabaseInterface::displayExportMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "0 - Main Menu" << '\n'
		          << "1 - Export Table" << '\n'
			      << "2 - Export Database" << '\n'			      
			      << "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
			return;
		case '1':
			clearScreen();
			showAllRecords();
			exportTableToFile();
			continueScreen();
			break;
		case '2':
			clearScreen();
			exportDatabaseToFile();
			continueScreen();
			break;		

		default:
			;
		}
	}
}
void DatabaseInterface::displayImportMenu()
{
	std::string menuStr;

	while (true)
	{
		clearScreen();

		std::cout << "0 - Main Menu" << '\n'
		    << "1 - Overwrite All" << '\n'
			<< "2 - Add to existing" << '\n'			
			<< "Enter a number and press enter: ";

		std::getline(std::cin, menuStr);
		if (menuStr.length() > 1)
			menuStr = 'y';
		else if (menuStr.empty())
			menuStr = 'y';

		switch (menuStr.at(0))
		{
		case 'x':
			[[fallthrough]];
		case '0':
			return;
		case '1':
			if (!confirmScreen())
				break;

			clearScreen();
			clearRecords();
			importFileToDatabase();
			continueScreen();
			break;
		case '2':
			if (!confirmScreen())
				break;

			clearScreen();
			importFileToDatabase();
			continueScreen();
			break;		

		default:
			;
		}
	}
}

//Functions
void DatabaseInterface::addRecordFromUser()
{
	clearScreen();

	const unsigned int id = getNextId();

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

	output << exportDatabaseAsString();

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
		std::cout << '\n' << filename << " Synatx error!" << '\n' << '\n';
	else
	{
		showAllRecords();
		std::cout << "Successfully imported Database!" << '\n' << '\n';		
	}
}
bool DatabaseInterface::databaseIsEmpty() const
{
	if(isDatabaseEmpty())
	{
		clearScreen();
		std::cout << "Database is empty!" << '\n' << '\n';
		continueScreen();
		return true;
	}

	return false;
}
void DatabaseInterface::clearDatabase()
{
	clearRecords();

	std::cout << '\n' << "Database cleared successfully!" << '\n' << '\n';
}

//Utility Functions
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

//Getters
std::string DatabaseInterface::getNameFromUser() const
{
	std::string temp;

	std::cin.clear();
	std::getline(std::cin, temp);

	while(!validateName(temp))
	{
		std::cout << '\n' << "Wrong Input!" << '\n' << "Please try again: ";
		std::cin.clear();
		std::getline(std::cin, temp);
	}

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

	while (!checkRecordIndex(index))
	{
		if (idStr == "x" || idStr == "X")
		{
			index = -1;
			break;
		}

		std::cout << '\n' << "Invalid Input." << '\n'
			<< "Please try again or press 'x' to cancel: ";
		std::getline(std::cin, idStr);
	}

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
	const unsigned int recordsSize = getNextId();

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

	while (!validateFilename(filename)) //Handle Wrong Input
	{
		std::cout << '\n' << "Wrong Input!" << '\n' << "Please try again: ";
		std::cin.clear();
		std::getline(std::cin, filename);
	}

	return filename;
}

//Table Functions
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