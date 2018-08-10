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

	//Getters
	Record getRecordByIndex(unsigned int index);
	unsigned int getNextId() const;

	// Setters
	void setName(unsigned int index, const std::string& name, bool isFirstname);

	//Checkers
	bool checkRecordIndex(unsigned int index) const;

	//Validators
	static bool validateName(std::string& name);
	static bool validateFilename(std::string& filename);
	
private:
	//Setters
	void setId(unsigned int index);

	//Vectors
	std::vector<Record> m_records;
};