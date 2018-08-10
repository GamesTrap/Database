#pragma once

#include <string>
#include <vector>

class TextTable
{
public:
	//Constructor
	explicit TextTable(char horizontal = '-', char vertical = '|', char corner = '+');

	//External Table Functions
	void add(std::string const& content);
	void clearTextTable();
	void endOfRow();

	//Operator Overloader
	friend std::ostream& operator<<(std::ostream& stream, TextTable const& table);

private:
	//Getters
	std::string getRuler() const;
	std::vector<std::vector<std::string>> const& getRows() const;
	char getVerticalChar() const;
	int getWidth(std::size_t i) const;
	std::size_t getColumns() const;

	//Internal Table Functions
	void determineWidths() const;
	static std::string repeat(std::size_t times, char c);


	//Variables
	char m_horizontal;
	char m_vertical;
	char m_corner;

	//Vectors
	std::vector<std::string> m_current;
	std::vector<unsigned int> mutable m_width;
	std::vector<std::vector<std::string>> m_rows;
};