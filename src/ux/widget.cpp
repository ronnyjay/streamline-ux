#include <ux/widget.hpp>

using namespace ux;

widget::widget(const int height, const int width, const int y, const int x)
    : m_updated(false), m_hidden(false), m_border(false), m_status(idle)
{
    m_window = newwin(height, width, y, x);

    keypad(m_window, true);  // enable terminal keypad
    nodelay(m_window, true); // non-blocking input
}

widget::~widget()
{
    delwin(m_window);
}

void widget::resize(const int height, const int width)
{
    wclear(m_window);
    wresize(m_window, height, width);

    set_updated(true);
}

void widget::position(const int y, const int x)
{
    wclear(m_window);
    mvwin(m_window, y, x);

    set_updated(true);
}

void widget::refresh()
{
    werase(m_window);
    wrefresh(m_window);
}

const bool widget::updated()
{
    return m_updated;
}

void widget::set_updated(const bool val)
{
    m_updated = val;
}

const status widget::get_status()
{
    return m_status;
}

void widget::set_status(const status s)
{
    m_status = s;

    set_updated(true);
}

const bool widget::hidden()
{
    return m_hidden;
}

void widget::set_hidden(const bool val)
{
    m_hidden = val;

    set_updated(true);
}

const bool widget::has_border()
{
    return m_border;
}

void widget::set_border(const bool val)
{
    m_border = val;
}

void widget::box()
{
    ::box(m_window, 0, 0);
    wrefresh(m_window);
}

const int widget::read_char()
{
    return wgetch(m_window);
}

void widget::move_cursor_to(const int y, const int x)
{
    wmove(m_window, y, x);
    wrefresh(m_window);
}

const int widget::height()
{
    return getmaxy(m_window);
}

const int widget::width()
{
    return getmaxx(m_window);
}

void widget::on_resize(std::function<void()> callback)
{
    m_listener.on("resize", callback);
}

void widget::printline(const std::basic_string<char> line)
{
    waddstr(m_window, line.c_str());
    wrefresh(m_window);
}

void widget::printline(const std::basic_string<char> line, const int y, const int x)
{
    wmove(m_window, y, x);
    printline(line);
}

void widget::printline(const std::basic_string<char> line, color c, attribute a)
{
    wattron(m_window, COLOR_PAIR(c));
    wattron(m_window, a);
    printline(line);
    wattroff(m_window, a);
    wattroff(m_window, COLOR_PAIR(c));
}

void widget::printline(const std::basic_string<char> line, const int y, const int x, color c, attribute a)
{
    wmove(m_window, y, x);
    printline(line, c, a);
}

void widget::printline(const std::basic_string<wchar_t> line)
{
    waddwstr(m_window, line.c_str());
    wrefresh(m_window);
}

void widget::printline(const std::basic_string<wchar_t> line, const int y, const int x)
{
    wmove(m_window, y, x);
    printline(line);
}

void widget::printline(const std::basic_string<wchar_t> line, color c, attribute a)
{
    wattron(m_window, COLOR_PAIR(c));
    wattron(m_window, a);
    printline(line);
    wattroff(m_window, a);
    wattroff(m_window, COLOR_PAIR(c));
}

void widget::printline(const std::basic_string<wchar_t> line, const int y, const int x, color c, attribute a)
{
    wmove(m_window, y, x);
    printline(line, c, a);
}
