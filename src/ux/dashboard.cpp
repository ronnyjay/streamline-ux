#include <ux/dashboard.hpp>

#include <stdexcept>

using namespace ux;

dashboard::dashboard(const int height, const int width, const int y, const int x) : widget(height, width, y, x)
{
}

void dashboard::display()
{
    refresh();

    if (hidden())
    {
        return;
    }

    if (has_border())
    {
        box();
    }

    uint16_t row = 1;

    for (const auto &table : m_tables)
    {
        const auto header = table.first;
        const auto data = table.second;

        if (row >= height() - TABLE_PADDING)
        {
            continue;
        }

        printline(header, row, (width() - header.length()) / 2, white, bold);

        for (const auto &entry : data)
        {
            if (row++ >= height())
            {
                break;
            }

            if (entry.length() >= (size_t)(width() - TABLE_PADDING))
            {
                printline(entry.substr(0, width() - 7) + "...", row, 1);
            }
            else
            {
                printline(entry, row, 1);
            }
        }

        row += TABLE_PADDING;
    }
}

void dashboard::add_table(std::basic_string<char> table)
{
    m_tables.emplace(table, std::vector<std::basic_string<char>>());
}

void dashboard::insert_into_table(std::basic_string<char> table, std::basic_string<char> data)
{
    auto t = m_tables.find(table);

    if (t == m_tables.end())
    {
        throw std::runtime_error("Table does not exist");
    }

    t->second.emplace_back(data);

    set_updated(true);
}

void dashboard::clear_table(std::basic_string<char> table)
{
    auto t = m_tables.find(table);

    if (t == m_tables.end())
    {
        throw std::runtime_error("Table does not exist");
    }

    t->second.clear();

    set_updated(true);
}