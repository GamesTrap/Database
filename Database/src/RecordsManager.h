#pragma once

#include "Record.h"
#include <vector>

class RecordsManager
{
protected:	
	//Adds a Record to m_records
	void addRecord(const std::string& Firstname, const std::string& Lastname);


	//Returns next ID for a new Record
	std::size_t getNextId() const;

private:
	//Returns Index from a Record
	std::size_t getIndex(std::size_t ID);
	std::size_t getIndex(const std::string& Name, bool isFirstname);

	//Returns ID from a Record
	std::size_t getId(std::size_t Index);
	std::size_t getId(const std::string& Name, bool isFirstname);

	//Returns Name from a Record
	std::string getName(std::size_t Index, bool isFirstname);
	std::string getName(const std::string& Name, bool isFirstname);


	//Sets new ID or new Name
	bool setId(std::size_t OldId, std::size_t NewId);
	bool setName(const std::string& Name, bool isFirstname);


	//Removes a Record from m_records
	bool removeRecordIndex(std::size_t Index);
	bool removeRecordId(std::size_t ID);
	bool removeRecord(const std::string& Name);


	//Removes all Records from m_records
	void clearRecords();


	//Swap Record with another Record
	bool swap(std::size_t OldId, std::size_t NewId);
	bool swap(std::size_t OldId, const std::string& NewName, bool isFirstname);
	bool swap(const std::string& OldName, bool isFirstname, std::size_t NewId);
	bool swap(const std::string& OldName, bool isOldFirstname, const std::string& NewName, bool isNewFirstname);


	std::vector<Record> m_records;
};