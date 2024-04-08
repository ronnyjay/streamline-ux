#include <ux/common.hpp>

using namespace ux;

decorated_string::decorated_string(std::basic_string<char> data) : m_data(data), m_color(white), m_attribute(bold)
{
}

decorated_string::decorated_string(std::basic_string<char> data, ux::color color)
    : m_data(data), m_color(color), m_attribute(bold)
{
}

decorated_string::decorated_string(std::basic_string<char> data, ux::attribute attribute)
    : m_data(data), m_color(white), m_attribute(attribute)
{
}

decorated_string::decorated_string(std::basic_string<char> data, ux::color color, ux::attribute attribute)
    : m_data(data), m_color(color), m_attribute(attribute)
{
}

const std::basic_string<char> decorated_string::data()
{
    return m_data;
}

const ux::color decorated_string::color()
{
    return m_color;
}

const ux::attribute decorated_string::attribute()
{
    return m_attribute;
}