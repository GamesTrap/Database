#include "Database.h"

void Database::addRecord(const std::string& Firstname, const std::string& Lastname)
{
	RecordsManager::addRecord(Firstname, Lastname);
}