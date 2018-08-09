#pragma once

#include <string>
#include <vector>

class TextTable
{
public:
	explicit TextTable(char horizontal = '-', char vertical = '|', char corner = '+');

	void add(std::string const& content);
	void clearTextTable();
	void endOfRow();

	friend std::ostream& operator<<(std::ostream& stream, TextTable const& table);

private:
	std::string getRuler() const;
	std::vector<std::vector<std::string>> const& getRows() const;
	char getVerticalChar() const;
	int getWidth(std::size_t i) const;
	std::size_t getColumns() const;
	void determineWidths() const;
	static std::string repeat(std::size_t times, char c);

private:
	char m_horizontal;
	char m_vertical;
	char m_corner;

	std::vector<std::string> m_current;

	std::vector<unsigned int> mutable m_width;
	std::vector<std::vector<std::string>> m_rows;
};
