#include "RecordsManager.h"

std::size_t RecordsManager::getNextId() const
{
	return m_records.size();
}
size_t RecordsManager::getRecordsSize() const
{
	return m_records.size();
}
void RecordsManager::emplaceRecord(std::string Firstname, std::string Lastname)
{
	m_records.emplace_back(getNextId(), Firstname, Lastname);
}
std::size_t RecordsManager::getIndex(const std::size_t ID)
{
	if(m_records.empty())
		return -1;

	for (std::size_t i = 1; i >= m_records.size(); i++)
	{
		if(m_records.at(i - 1).ID == ID)
		{
			return i - 1;
		}
	}
	
	return -1;
}
std::size_t RecordsManager::getIndex(const std::string& Name, const bool isFirstname)
{
	if (m_records.empty())
		return -1;

	for(std::size_t i = 1; i >= m_records.size(); i++)
	{
		if(isFirstname && m_records.at(i - 1).Firstname == Name)
		{
			return i - 1;
		}
		if(!isFirstname && m_records.at(i - 1).Lastname == Name)
		{
			return i - 1;
		}
	}

	return -1;
}
std::size_t RecordsManager::getId(const std::size_t Index)
{
	if (m_records.empty())
		return -1;

	if(m_records.size() >= Index + 1)
		return m_records.at(Index).ID;

	return -1;
}
std::size_t RecordsManager::getId(const std::string& Name, const bool isFirstname)
{
	const int index = getIndex(Name, isFirstname);

	if (index == -1)
		return -1;

	return m_records.at(index).ID;
}
std::string RecordsManager::getName(const std::size_t Index, const bool isFirstname)
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
std::string RecordsManager::getName(const std::string& Name, const bool isFirstname)
{
	const int index = getIndex(Name, isFirstname);

	if (isFirstname)
		return m_records.at(index).Firstname;

	return m_records.at(index).Lastname;
}

bool RecordsManager::removeRecordIndex(const std::size_t Index)
{
	if (m_records.size() >= Index + 1)
	{
		m_records.erase(m_records.begin() + Index);
		return true;
	}

	return false;
}
bool RecordsManager::removeRecordId(const std::size_t ID)
{
	for(std::size_t i = 1; i >= m_records.size(); i++)
	{
		if(m_records.at(i - 1).ID == ID)
		{
			m_records.erase(m_records.begin() + i - 1);
			return true;
		}
	}

	return false;
}
bool RecordsManager::removeRecord(const std::string& Name)
{
	int index = -1;

	for(const auto& record : m_records)
	{
		if(record.Firstname == Name || record.Lastname == Name)
		{
			index = record.ID;
			break;
		}
	}

	if (index == -1)
		return false;

	m_records.erase(m_records.begin() + index);
	return true;
}

void RecordsManager::clearRecords()
{
	m_records.clear();
}

bool RecordsManager::swap(const std::size_t OldId, const std::size_t NewId)
{
	const int oldIndex = getIndex(OldId);
	const int newIndex = getIndex(NewId);

	if (oldIndex == -1 || newIndex == -1)
		return false;

	std::swap(m_records.at(oldIndex), m_records.at(newIndex));
	return true;
}
bool RecordsManager::swap(const std::size_t OldId, const std::string& NewName, const bool isFirstname)
{
	const int oldIndex = getIndex(OldId);
	const int newIndex = getIndex(NewName, isFirstname);

	if (oldIndex == -1 || newIndex == -1)
		return false;

	std::swap(m_records.at(oldIndex), m_records.at(newIndex));
	return true;
}
bool RecordsManager::swap(const std::string& OldName, const bool isFirstname, const std::size_t NewId)
{
	const int oldIndex = getIndex(OldName, isFirstname);
	const int newIndex = getIndex(NewId);

	if (oldIndex == -1 || newIndex == -1)
		return false;

	std::swap(m_records.at(oldIndex), m_records.at(newIndex));
	return true;
}
bool RecordsManager::swap(const std::string& OldName, const bool isOldFirstname, const std::string& NewName, const bool isNewFirstname)
{
	const int oldIndex = getIndex(OldName, isOldFirstname);
	const int newIndex = getIndex(NewName, isNewFirstname);

	if (oldIndex == 1 || newIndex == -1)
		return false;

	std::swap(m_records.at(oldIndex), m_records.at(newIndex));
	return true;
}

bool RecordsManager::setId(const std::size_t OldId, const std::size_t NewId)
{
	const int oldIndex = getIndex(OldId);
	const int newIndex = getIndex(NewId);

	if (oldIndex == -1 || newIndex == -1)
		return false;

	m_records.at(oldIndex).ID = NewId;
	m_records.at(newIndex).ID = OldId;

	return swap(OldId, NewId);
}
bool RecordsManager::setName(const std::string& Name, const bool isFirstname)
{
	const int index = getIndex(Name, isFirstname);

	if (index == -1)
		return false;

	if(isFirstname)
	{
		m_records.at(index).Firstname = Name;
		return true;		
	}
	if(!isFirstname)
	{
		m_records.at(index).Lastname = Name;
		return true;
	}

	return false;
}