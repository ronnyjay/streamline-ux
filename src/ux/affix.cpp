#include <ux/affix.hpp>

using namespace ux;

affix::affix()
{
}

affix &affix::add_segment(std::basic_string<char> data)
{
    segment s;
    init_segment(&s, data, white, normal);

    m_segments.emplace_back(s);

    return *this;
}

affix &affix::add_segment(std::basic_string<char> data, ux::color color)
{
    segment s;
    init_segment(&s, data, color, normal);

    m_segments.emplace_back(s);

    return *this;
}

affix &affix::add_segment(std::basic_string<char> data, ux::color color, ux::attribute attribute)
{
    segment s;
    init_segment(&s, data, color, attribute);

    m_segments.emplace_back(s);

    return *this;
}

affix &affix::set_segment(const int pos, std::basic_string<char> data)
{
    segment s;
    init_segment(&s, data, white, normal);

    if (pos >= (int)m_segments.size())
    {
        m_segments.resize(pos + 1);
    }

    m_segments[pos] = s;

    return *this;
}

affix &affix::set_segment(const int pos, std::basic_string<char> data, ux::color color)
{
    segment s;
    init_segment(&s, data, color, normal);

    if (pos >= (int)m_segments.size())
    {
        m_segments.resize(pos + 1);
    }

    m_segments[pos] = s;

    return *this;
}

affix &affix::set_segment(const int pos, std::basic_string<char> data, ux::color color, ux::attribute attribute)
{
    segment s;
    init_segment(&s, data, color, attribute);

    if (pos >= (int)m_segments.size())
    {
        m_segments.resize(pos + 1);
    }

    m_segments[pos] = s;

    return *this;
}

affix &affix::clear()
{
    m_segments.clear();

    return *this;
}

size_t affix::length()
{
    size_t len = 0;

    for (const auto &segment : m_segments)
    {
        len += segment.data.length();
    }

    return len;
}

const std::vector<segment> &affix::segments()
{
    return std::ref(m_segments);
}

void affix::init_segment(segment *s, std::basic_string<char> data, ux::color color, ux::attribute attribute)
{
    s->data = data;
    s->color = color;
    s->attribute = attribute;
}
