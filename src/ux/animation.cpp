#include <ux/animation.hpp>

using namespace ux;

animation::animation(const int height, const int width, const int y, const int x)
    : widget(height, width, y, x), m_last_updated(std::chrono::high_resolution_clock::now()), m_frame(0),
      m_foreground(magenta), m_background(white), m_speed(medium)
{
}

void animation::enable()
{
    set_status(active);
}

void animation::disable()
{
    set_status(complete);
}

const bool animation::finished()
{
    return false;
}

void animation::restart()
{
    set_frame(0);
}

const int animation::get_frame()
{
    return m_frame;
}

void animation::set_frame(const int val)
{
    m_frame = val;

    set_updated(true);
}

const speed animation::get_speed()
{
    return m_speed;
}

void animation::set_speed(const speed val)
{
    m_speed = val;
}

const color animation::foreground()
{
    return m_foreground;
}

const color animation::background()
{
    return m_background;
}

void animation::execute_action()
{
    using namespace std::chrono;

    auto current_time = high_resolution_clock::now();
    auto delta_time = duration_cast<milliseconds>(current_time - m_last_updated);

    if (delta_time <= milliseconds(m_speed))
    {
        return;
    }

    m_last_updated = current_time;

    set_updated(true);
}

loading_bar::loading_bar(const int height, const int width, const int y, const int x) : animation(height, width, y, x)
{
    m_bar = std::basic_string<wchar_t>(width - 1, unicode_block::full);
}

void loading_bar::resize(const int height, const int width)
{
    widget::resize(height, width);

    m_bar = std::basic_string<wchar_t>(width - 1, unicode_block::full);
}

void loading_bar::display()
{
    refresh();

    if (hidden() || get_status() == idle)
    {
        return;
    }

    int bar_size = width() - 1;

    if (has_border())
    {
        bar_size = bar_size - 1;

        box();
    }

    curs_set(false);

    if (finished())
    {
        restart();
    }

    printline(m_bar, 1, 1, background(), normal);
    printline(&m_bar[bar_size - 1] - get_frame(), 1, 1, foreground(), normal);

    set_frame(get_frame() + 1);

    curs_set(true);
}

const bool loading_bar::finished()
{
    return get_frame() > width() - 1;
}

ticker::ticker(const int height, const int width, const int y, const int x)
    : animation(height, width, y, x), m_cursor(0)
{
}

void ticker::display()
{
    refresh();

    if (hidden() || get_status() == idle)
    {
        return;
    }

    if (has_border())
    {
        box();
    }

    if (finished())
    {
        restart();
    }

    if (colliding())
    {
        set_frame(1);
    }
    const int32_t print_width = width() - 1;

    int32_t y = 1, x = 1;

    std::basic_string<char> data;

    // adding to the window
    if (get_cursor() < print_width)
    {
        data = m_text.substr(0, get_frame());
        x = print_width - get_cursor();
    }
    // window is full, adjust what is being shown
    else
    {
        if (out_of_range())
        {
            set_frame(1);
        }

        data = m_text.substr(get_frame(), std::min(print_width, (int)m_text.length()));
    }

    printline(data, y, x, foreground(), bold);

    set_frame(get_frame() + 1);
    set_cursor(get_cursor() + 1);
}

const bool ticker::finished()
{
    return (get_frame() + 1 > (int)m_text.length() && get_cursor() > width() - 1);
}

void ticker::restart()
{
    set_frame(0);
    set_cursor(0);
}

void ticker::set_text(std::basic_string<char> text)
{
    m_text = text;
}

const int ticker::get_cursor()
{
    return m_cursor;
}

void ticker::set_cursor(const int val)
{
    m_cursor = val;
}

const bool ticker::colliding()
{
    return (get_frame() >= width() - 1 && get_cursor() <= width() - 1);
}

const bool ticker::out_of_range()
{
    return (get_frame() > (int)m_text.length());
}