#pragma once

#include <ux/common.hpp>

#include <string>
#include <vector>

namespace ux
{

typedef struct segment
{
    std::basic_string<char> data;
    ux::color color;
    ux::attribute attribute;
} segment;

class affix
{
  public:
    affix();

    affix &add_segment(std::basic_string<char>);
    affix &add_segment(std::basic_string<char>, color);
    affix &add_segment(std::basic_string<char>, color, attribute);

    affix &set_segment(const int, std::basic_string<char>);
    affix &set_segment(const int, std::basic_string<char>, color);
    affix &set_segment(const int, std::basic_string<char>, color, attribute);

    affix &clear();

    const std::vector<segment> &segments();

    size_t length();

  private:
    std::vector<segment> m_segments;

    void init_segment(segment *, std::basic_string<char>, color, attribute);
};

}; // namespace ux