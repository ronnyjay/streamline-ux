#pragma once

#include <curses.h>
#include <string>

namespace ux
{

typedef enum
{
    white = 0,
    yellow = 1,
    magenta = 2,
    cyan = 3,
    green = 4,
    blue = 5,
    red = 6,
    black = 7
} color;

typedef enum : unsigned int
{
    normal = (1U - 1U),
    bold = NCURSES_BITS(1U, 13)
} attribute;

typedef enum
{
    top = 0,
    right = 1,
    left = 2,
    box = 3,
    none = 4
} border;

typedef enum
{
    idle,
    active,
    complete
} status;

typedef enum
{
    slow = 175,
    medium = 125,
    fast = 75,
} speed;

typedef enum : wchar_t
{
    full = U'\u2588',
    left_half = U'\u258C',
    right_half = U'\u2590',
    left_eigth = U'\u258E',
    right_eigth = U'\u2595',
} unicode_block;

typedef enum : wchar_t
{
    dot = U'\u2022',
} unicode_symbol;

class decorated_string
{
  public:
    decorated_string(std::basic_string<char>);
    decorated_string(std::basic_string<char>, ux::color);
    decorated_string(std::basic_string<char>, ux::attribute);
    decorated_string(std::basic_string<char>, ux::color, ux::attribute);

    const std::basic_string<char> data();
    const ux::color color();
    const ux::attribute attribute();

  private:
    std::basic_string<char> m_data;
    ux::color m_color;
    ux::attribute m_attribute;
};

}; // namespace ux