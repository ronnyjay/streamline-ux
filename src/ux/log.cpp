#include <ux/log.hpp>

using namespace ux;

log::log(const int height, const int width, const int y, const int x) : widget(height, width, y, x)
{
}

void log::display()
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

    uint16_t x = BORDER_OFFSET;
    uint16_t y = 1 + x;

    const uint16_t line_length = width() - (2 * BORDER_OFFSET);

    for (auto it = m_entries.rbegin(); it != m_entries.rend(); ++it)
    {
        const auto entry = std::basic_string<char>(it->first.data().length() + TAG_PADDING, ' ') + it->second;

        const uint16_t whole_lines = entry.length() / line_length;
        const uint16_t remainder = entry.length() % line_length;

        int start = entry.length() - line_length - remainder;

        if (remainder)
        {
            if (y >= height() - BORDER_OFFSET)
            {
                break;
            }

            printline(entry.c_str() + (whole_lines * line_length), height() - y++, x);
        }

        for (int i = 0; i < whole_lines; i++)
        {

            printline(entry.substr(start, line_length), height() - y++, x);

            start -= line_length;

            if (y >= height() - BORDER_OFFSET)
            {
                break;
            }
        }

        printline("[", height() - y + 1, x, ux::white, ux::bold);
        printline(it->first.data(), it->first.color(), it->first.attribute());
        printline("]: ", ux::white, ux::bold);
    }
}

void log::insert(decorated_string sender, std::basic_string<char> data)
{
    if ((int)m_entries.size() >= height() - BORDER_OFFSET)
    {
        m_entries.pop_front();
    }

    m_entries.push_back(std::pair<decorated_string, std::basic_string<char>>(sender, data));

    set_updated(true);
}
