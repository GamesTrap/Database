#include "TextTable.h"
#include <iomanip>

TextTable::TextTable(const char horizontal, const char vertical, const char corner)
	: m_horizontal{ horizontal }, m_vertical{ vertical }, m_corner{ corner }
{}

void TextTable::setup() const
{
	determineWidths();
	setupAlignment();
}

void TextTable::add(std::string const &content)
{
	m_current.push_back(content);
}

std::string TextTable::ruler() const
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

std::vector<TextTable::row> const& TextTable::rows() const
{
	return m_rows;
}

void TextTable::endOfRow()
{
	m_rows.push_back(m_current);
	m_current.assign(0, "");
}

char TextTable::vertical() const
{
	return m_vertical;
}

TextTable::Alignment TextTable::alignment(const unsigned int i) const
{
	return m_alignment.at(i);
}

int TextTable::width(const unsigned int i) const
{
	return m_width.at(i);
}

void TextTable::determineWidths() const
{
	m_width.assign(columns(), 0);
	for (const auto& row : m_rows)
	{
		for (std::size_t i = 0; i < row.size(); ++i) 
		{
			m_width.at(i) = m_width.at(i) > row.at(i).size() ? m_width.at(i) : row.at(i).size();
		}
	}
}

std::size_t TextTable::columns() const
{
	return m_rows.at(0).size();
}

void TextTable::setupAlignment() const //////////////////////////////////
{
	for (std::size_t i = 0; i < columns(); ++i) 
	{
		if (m_alignment.find(i) == m_alignment.end()) 
		{
			m_alignment[i] = Alignment::LEFT;
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

std::ostream& operator<<(std::ostream& stream, TextTable const& table)
{
	table.setup();
	stream << table.ruler() << '\n';
	for (auto rowIterator = table.rows().begin(); rowIterator != table.rows().end(); ++rowIterator)
	{
		auto const & row = *rowIterator;
		stream << table.vertical();
		for (std::size_t i = 0; i < row.size(); ++i) 
		{
			const auto alignment = table.alignment(i) == TextTable::Alignment::LEFT ? std::left : std::right;
			stream << std::setw(table.width(i)) << alignment << row.at(i);
			stream << table.vertical();
		}
		stream << '\n';
		stream << table.ruler() << '\n';
	}

	return stream;
}