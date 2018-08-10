#pragma once

#include "Record.h"
#include <vector>

class Database
{
public:
	//Functions
	void addRecord(unsigned int id, std::string Firstname, std::string Lastname);
	bool removeRecord(unsigned int index);
	void clearRecords();
	std::string exportDatabaseAsString();
	bool importDatabase(std::vector<std::string> &CSVs, unsigned int elements);
	bool isDatabaseEmpty() const;

	//External Getters
	Record getRecordByIndex(unsigned int index);
	unsigned int getNextId() const;

	//External Setters
	void setFirstname(unsigned int index, const std::string& Firstname);
	void setLastname(unsigned int index, const std::string& Lastname);

	//Checkers
	bool checkRecordIndex(unsigned int index) const;

	//Validators
	static bool validateName(std::string& name);
	static bool validateFilename(std::string& filename);
	
private:
	//Internal Getters
	std::string getName(unsigned int Index, bool isFirstname);

	//Internal Setters
	void setId(unsigned int index);

	//Vectors
	std::vector<Record> m_records;
};