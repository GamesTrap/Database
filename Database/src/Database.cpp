#include "Database.h"

#include <cctype>

//Functions
void Database::addRecord(unsigned int id, std::string Firstname, std::string Lastname)
{
	m_records.emplace_back(id, Firstname, Lastname);
}
bool Database::removeRecord(const unsigned int index)
{
	if (!checkRecordIndex(index))
		return false;

	m_records.erase(m_records.begin() + index);

	for (unsigned int i = index; i < getNextId(); i++) { setId(i); }

	return true;
}
void Database::clearRecords()
{
	m_records.clear();
}
std::string Database::exportDatabaseAsString()
{
	std::string temp;

	for (unsigned int i = 0; i < m_records.size(); i++)
	{
		if (i == 0)
			temp += m_records.at(i).Firstname + "," + m_records.at(i).Lastname + '\n';
		else
			temp += "," + m_records.at(i).Firstname + "," + m_records.at(i).Lastname + '\n';
	}

	return temp;
}
bool Database::importDatabase(std::vector<std::string> &CSVs, const unsigned int elements)
{
	bool isCorrect = true;

	for (unsigned int i = 0; i < elements; i += 2)
	{
		std::string firstname = CSVs.at(i + 1);

		if (!validateName(firstname))
			isCorrect = false;

		std::string lastname = CSVs.at(i + 2);

		if (!validateName(lastname))
			isCorrect = false;

	    if(isCorrect)
		    m_records.emplace_back(getNextId(), firstname, lastname);
	}

	return isCorrect;
}
bool Database::isDatabaseEmpty() const
{
	return getNextId() <= 0;
}

//External Getters
Record Database::getRecordByIndex(const unsigned int index) { return Record(m_records.at(index)); }
unsigned int Database::getNextId() const { return static_cast<unsigned int>(m_records.size()); }

//External Setters
void Database::setFirstname(const unsigned int index, const std::string& Firstname)
{
	m_records.at(index).Firstname = Firstname;
}
void Database::setLastname(const unsigned int index, const std::string& Lastname)
{
	m_records.at(index).Lastname = Lastname;
}

//Checkers
bool Database::checkRecordIndex(const unsigned int index) const
{
	if (m_records.empty())
		return false;

	return getNextId() > index;
}

//Validators
bool Database::validateName(std::string& name)
{
	bool isCorrect = false;

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

	return isCorrect;
}
bool Database::validateFilename(std::string& filename)
{
	bool isCorrect = true;

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

	return isCorrect;
}

//Internal Getters
std::string Database::getName(const unsigned int Index, const bool isFirstname)
{
	if (m_records.empty())
		return "";

	if (m_records.size() >= Index + 1)
	{
		if (isFirstname)
			return m_records.at(Index).Firstname;

		return m_records.at(Index).Lastname;
	}

	return "";
}

//Internal Setters
void Database::setId(const unsigned int index) { m_records.at(index).ID = index; }