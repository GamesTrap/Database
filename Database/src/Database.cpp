#include "Database.h"

//Public:
void Database::addRecord(std::string Firstname, std::string Lastname)
{
	m_records.emplace_back(getNextId(), Firstname, Lastname);
}
bool Database::checkRecordIndex(const unsigned int index) const
{
	if (m_records.empty())
		return false;

	return getRecordsSize() > index;
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