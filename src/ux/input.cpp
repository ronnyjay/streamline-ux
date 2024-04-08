#include <ux/input.hpp>

#include <thread>

using namespace ux;

extern volatile std::atomic_bool running;

input::input(const int height, const int width, const int y, const int x)
    : widget(height, width, y, x), m_encrypted(false), m_character_count(false)
{
}

void input::display()
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

    if (m_character_count)
    {
        auto read_chars = std::to_string(m_buffer.size());
        auto total_chars = std::to_string(m_buffer.length());
        auto whitespace = std::basic_string<char>(total_chars.length() - read_chars.length(), ' ');

        m_suffix.clear().set_segment(0, whitespace + read_chars + "/" + total_chars, white, bold);
    }

    int x = 0;

    // display prefix
    for (const auto &segment : m_prefix.segments())
    {
        printline(segment.data, BORDER_OFFSET, x + BORDER_OFFSET, segment.color, segment.attribute);
        x += segment.data.length();
    }

    // display suffix
    for (const auto &segment : m_suffix.segments())
    {
        printline(segment.data, BORDER_OFFSET, (width() - m_suffix.length()) - BORDER_OFFSET, segment.color,
                  segment.attribute);
    }

    if (width() < (int)m_prefix.length() + (int)m_suffix.length())
    {
        return;
    }

    // display input
    if (m_encrypted)
    {
        auto input = std::basic_string<wchar_t>(m_buffer.get_offset(CHAR_OFFSET).length(), unicode_symbol::dot)
                         .substr(0, INPUT_WIDTH - m_prefix.length() - 1);

        // enable/disable last character shown on screen
        if ((input.length() / (INPUT_WIDTH - m_prefix.length() - 1)) == 1 && m_buffer.cursor_distance() % 2)
        {
            input.at(input.length() - 1) = ' ';
        }

        printline(input, BORDER_OFFSET, m_prefix.length() + BORDER_OFFSET);
    }
    else
    {
        printline(m_buffer.get_offset(CHAR_OFFSET).substr(0, INPUT_WIDTH - m_prefix.length() - 1), BORDER_OFFSET,
                  m_prefix.length() + BORDER_OFFSET);
    }
}

const bool input::updated()
{
    return m_buffer.get_changed();
}

void input::set_updated(const bool val)
{
    m_buffer.set_changed(val);
}

void input::set_encrypted(const bool val)
{
    m_encrypted = val;
}

void input::show_character_count(const bool val)

{
    m_character_count = val;
}

affix &input::prefix()
{
    return std::ref(m_prefix);
}

affix &input::suffix()
{
    return std::ref(m_suffix);
}

const std::basic_string<char> input::read_line()
{
    set_status(active);
    set_hidden(false);

    while (running && get_status() == active)
    {
        std::this_thread::yield();
    }

    std::basic_string<char> line = m_buffer.get_offset(0);
    m_buffer.clear();

    return line;
}

void input::execute_action()
{
    move_cursor_to(BORDER_OFFSET, CURSOR_POSITION);

    int c = read_char();

    if (c < 32 || c > 126)
    {
        switch (c)
        {
        case KEY_BACKSPACE:
        case KEY_DELETE:
            m_buffer.backspace();
            break;
        case KEY_DC:
            m_buffer.del();
            break;
        case KEY_RIGHT:
            m_buffer.right();
            break;
        case KEY_LEFT:
            m_buffer.left();
            break;
        case KEY_NEWLINE:
            set_status(complete);
            set_hidden(true);
        default:
            break;
        }
    }
    else
    {
        m_buffer.insert(c);
    }
}
