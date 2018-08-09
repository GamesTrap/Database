#include "Database.h"

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

std::string Database::toString()
{
	std::string temp;

	for(unsigned int i = 0; i < m_records.size(); i++)
	{
		if (i == 0)
			temp += std::to_string(m_records.at(i).ID) + "," + m_records.at(i).Firstname + "," + m_records.at(i).Lastname + '\n';
		else
		    temp += "," + std::to_string(m_records.at(i).ID) + "," + m_records.at(i).Firstname + "," + m_records.at(i).Lastname + '\n';
	}

	return temp;
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
