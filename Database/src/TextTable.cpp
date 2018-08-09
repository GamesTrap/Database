#include "TextTable.h"
#include <iomanip>

//Public:
TextTable::TextTable(const char horizontal, const char vertical, const char corner)
	: m_horizontal{horizontal}, m_vertical{vertical}, m_corner{corner} {}

void TextTable::add(std::string const& content) { m_current.push_back(content); }

void TextTable::clearTextTable()
{
	m_width.clear();
	m_rows.clear();
	m_current.clear();
}

void TextTable::endOfRow()
{
	m_rows.push_back(m_current);
	m_current.assign(0, "");
}

//Private:
std::string TextTable::getRuler() const
{
	std::string result;
	result += m_corner;
	for (auto& width : m_width)
	{
		result += repeat(width, m_horizontal);
		result += m_corner;
	}

	return result;
}

std::vector<std::vector<std::string>> const& TextTable::getRows() const { return m_rows; }

char TextTable::getVerticalChar() const { return m_vertical; }

int TextTable::getWidth(const std::size_t i) const { return m_width.at(i); }

std::size_t TextTable::getColumns() const { return m_rows.at(0).size(); }

void TextTable::determineWidths() const
{
	m_width.assign(getColumns(), 0);
	for (const auto& row : m_rows)
	{
		for (std::size_t i = 0; i < row.size(); ++i)
		{
			m_width.at(i) = static_cast<unsigned int>(m_width.at(i) > row.at(i).size()
				                                          ? m_width.at(i)
				                                          : row.at(i).size());
		}
	}
}

std::string TextTable::repeat(std::size_t times, const char c)
{
	std::string result;
	for (; times > 0; --times)
		result += c;

	return result;
}

//Outside of TextTable
std::ostream& operator<<(std::ostream& stream, TextTable const& table)
{
	table.determineWidths();
	stream << table.getRuler() << '\n';
	for (auto rowIterator = table.getRows().begin(); rowIterator != table.getRows().end(); ++rowIterator)
	{
		auto const& row = *rowIterator;
		stream << table.getVerticalChar();
		for (std::size_t i = 0; i < row.size(); ++i)
		{
			const auto alignment = std::left;
			stream << std::setw(table.getWidth(i)) << alignment << row.at(i);
			stream << table.getVerticalChar();
		}
		stream << '\n';
		stream << table.getRuler() << '\n';
	}

	return stream;
}
