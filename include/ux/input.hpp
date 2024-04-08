#pragma once

#include <ux/affix.hpp>
#include <ux/buffer.hpp>
#include <ux/renderer.hpp>
#include <ux/widget.hpp>

#define KEY_DELETE 127
#define KEY_NEWLINE '\n'

#define INPUT_WIDTH ((width() - m_suffix.length()) - (2 * BORDER_OFFSET))

#define CURSOR_DISTANCE (m_buffer.cursor_distance() + m_prefix.length())
#define CURSOR_POSITION (std::min(CURSOR_DISTANCE, (INPUT_WIDTH - 1)) + BORDER_OFFSET)

#define CHAR_OFFSET (std::max(((int)CURSOR_DISTANCE - ((int)INPUT_WIDTH)) + 1, 0))

namespace ux
{

class input : public widget
{
  public:
    input(const int, const int, const int, const int);

    virtual void display() override;

    virtual const bool updated() override;
    virtual void set_updated(const bool) override;

    void set_encrypted(const bool);
    void show_character_count(const bool);

    affix &prefix();
    affix &suffix();

    const std::basic_string<char> read_line();

  protected:
    virtual void execute_action() override;

  private:
    affix m_prefix;
    affix m_suffix;

    buffer m_buffer;

    std::atomic_bool m_encrypted;
    std::atomic_bool m_character_count;
};

}; // namespace ux