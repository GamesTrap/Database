#include "Database.h"

//Public:
void Database::addRecord(unsigned int id, std::string Firstname, std::string Lastname)
{
	m_records.emplace_back(id, Firstname, Lastname);
}
bool Database::checkRecordIndex(const unsigned int index) const
{
	if (m_records.empty())
		return false;

	return getRecordsSize() > index;
}

bool Database::removeRecord(const unsigned int index)
{
	if (!checkRecordIndex(index))
		return false;

	m_records.erase(m_records.begin() + index);

	for(unsigned int i = index; i < getRecordsSize(); i++)
	{
		setId(i);
	}

	return true;
}

Record Database::getRecordByIndex(const unsigned int index)
{
	return Record(m_records.at(index));
}
unsigned int Database::getNextId() const
{
	return m_records.size();
}
unsigned int Database::getRecordsSize() const
{
	return m_records.size();
}

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

void Database::setId(const unsigned index)
{
	m_records.at(index).ID = index;
}