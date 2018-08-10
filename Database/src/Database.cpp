#include "Database.h"

#include <cctype>

//Public:
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

void Database::setFirstname(const unsigned int index, const std::string& Firstname)
{
	m_records.at(index).Firstname = Firstname;
}

void Database::setLastname(const unsigned int index, const std::string& Lastname)
{
	m_records.at(index).Lastname = Lastname;
}

Record Database::getRecordByIndex(const unsigned int index) { return Record(m_records.at(index)); }
unsigned int Database::getNextId() const { return m_records.size(); }

bool Database::checkRecordIndex(const unsigned int index) const
{
	if (m_records.empty())
		return false;

	return getNextId() > index;
}

std::string Database::exporrtDatabaseAsString()
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

bool Database::importDatabase(std::vector<std::string> &CSVs, unsigned int elements)
{
	bool isCorrect = true;

	for (unsigned int i = 0; i < elements; i += 2)
	{
		if (CSVs.at(i + 1).empty())
			isCorrect = false;
		if (CSVs.at(i + 1).at(0) == ' ')
			isCorrect = false;
		if (CSVs.at(i + 1).at(CSVs.at(i + 1).size() - 1) == ' ')
			isCorrect = false;
		for (auto& ch : CSVs.at(i + 1))
			if (!std::isalpha(ch) || std::isdigit(ch))
				isCorrect = ch != ' ';

		std::string firstname = CSVs.at(i + 1);

		if (CSVs.at(i + 2).empty())
			isCorrect = false;
		if (CSVs.at(i + 2).at(0) == ' ')
			isCorrect = false;
		if (CSVs.at(i + 2).at(CSVs.at(i + 2).size() - 1) == ' ')
			isCorrect = false;
		for (auto& ch : CSVs.at(i + 2))
			if (!std::isalpha(ch) || std::isdigit(ch))
				isCorrect = ch != ' ';

		std::string lastname = CSVs.at(i + 2);

		m_records.emplace_back(getNextId(), firstname, lastname);
	}

	return isCorrect;
}

bool Database::validateName(std::string& name)
{
	bool isCorrect = true;

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

bool Database::validateIndex(int& index) const
{
	return checkRecordIndex(index);
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


void Database::clearRecords()
{
	m_records.clear();
}

bool Database::isDatabaseEmpty() const
{
	return getNextId() <= 0;
}

//Private:
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

void Database::setId(const unsigned int index) { m_records.at(index).ID = index; }
