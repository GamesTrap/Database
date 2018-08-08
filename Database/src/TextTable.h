#pragma once

#include <string>
#include <vector>
#include <map>

class TextTable
{
public:
	enum class Alignment { LEFT, RIGHT };

	typedef std::vector<std::string> row;


	explicit TextTable(char horizontal = '-', char vertical = '|', char corner = '+');

	void setup() const;
	void add(std::string const &content);
	void clear();
	std::string ruler() const;
	std::vector<row> const &rows() const;
	void endOfRow();
	char vertical() const;
	Alignment alignment(std::size_t i) const;
	int width(std::size_t i) const;

private:
	char m_horizontal;
	char m_vertical;
	char m_corner;

	row m_current;

	std::vector<unsigned int> mutable m_width;
	std::vector<row> m_rows;

	std::map<std::size_t, Alignment > mutable m_alignment;

	void determineWidths() const;
	void setupAlignment() const;
	std::size_t columns() const;
	static std::string repeat(std::size_t times, char c);
};

std::ostream& operator<<(std::ostream &stream, TextTable const &table);