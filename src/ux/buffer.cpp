#include <ux/buffer.hpp>

#include <stdexcept>

using namespace ux;

buffer::buffer() : m_length(DEFAULT_BUFFER_LENGTH), m_changed(false)
{
    m_buffer = new char[m_length];

    if (!m_buffer)
    {
        throw std::runtime_error("Unable to allocate buffer");
    }

    m_buffer[0] = '\0';

    m_cursor = m_buffer;
    m_end = m_buffer;
    m_back = m_buffer + m_length;
}

buffer::buffer(size_t length) : m_length(length), m_changed(true)
{
    m_buffer = new char[m_length];

    if (!m_buffer)
    {
        throw std::runtime_error("Unable to allocate buffer");
    }

    m_buffer[0] = '\0';

    m_cursor = m_buffer;
    m_end = m_buffer;
    m_back = m_buffer + m_length;
}

bool buffer::get_changed()
{
    return m_changed;
}

void buffer::set_changed(const bool val)
{
    m_changed = val;
}

int buffer::cursor_distance()
{
    return m_cursor - m_buffer;
}

int buffer::length()
{
    return m_length;
}

int buffer::size()
{
    return m_end - m_buffer;
}

std::string buffer::get_offset(int offset)
{
    return std::string(m_buffer + offset);
}

void buffer::insert(int c)
{
    char *t;
    char temp;
    char next;
    t = m_cursor;

    if (m_cursor != m_back)
    {
        m_cursor++;
    }

    next = c;
    while (t != m_back && next != '\0')
    {
        temp = *t;
        *t = next;
        next = temp;
        t++;
    }

    *t = '\0';
    m_end = t;

    m_changed = true;
}

void buffer::backspace()
{
    char temp;
    char next;

    char *c;
    c = m_end;

    if (m_cursor != m_buffer)
    {
        m_end--;
        m_cursor--;
    }

    temp = *c;
    while (c != m_cursor)
    {
        next = temp;
        c--;
        temp = *c;
        *c = next;
    }

    m_changed = true;
}

void buffer::del()
{
    char temp;
    char next;

    char *c;
    c = m_end;

    while (c != m_cursor - 1)
    {
        temp = *c;
        *c = next;
        next = temp;
        c--;
    }

    m_changed = true;
}

void buffer::right()
{
    if (m_cursor != m_end)
    {
        m_cursor++;
    }

    m_changed = true;
}

void buffer::left()
{
    if (m_cursor != m_buffer)
    {
        m_cursor--;
    }

    m_changed = true;
}

void buffer::clear()
{
    m_buffer[0] = '\0';
    m_end = m_buffer;
    m_cursor = m_buffer;

    m_changed = true;
}

void buffer::resize(size_t length)
{
    delete[] m_buffer;

    m_buffer = new char[length];

    if (!m_buffer)
    {
        throw std::runtime_error("Unable to allocate buffer");
    }

    m_buffer[0] = '\0';

    m_cursor = m_buffer;
    m_end = m_buffer;
    m_back = m_buffer + length;

    m_length = length;
}

buffer::~buffer()
{
    delete[] m_buffer;
}