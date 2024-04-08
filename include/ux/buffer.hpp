#pragma once

#include <atomic>
#include <cstdint>
#include <string>

#define DEFAULT_BUFFER_LENGTH 1024

namespace ux
{

class buffer
{
  public:
    buffer();
    buffer(size_t);

    bool get_changed();
    void set_changed(const bool);

    int cursor_distance();
    int length();
    int size();

    std::string get_offset(int);

    void insert(int);
    void backspace();
    void del();
    void right();
    void left();

    void clear();
    void resize(size_t);

    ~buffer();

  private:
    char *m_buffer; // pointer to the start of the buffer
    char *m_cursor; // pointer to the cursor position
    char *m_end;    // pointer to null terminator
    char *m_back;   // pointer to the last byte in the buffer

    uint32_t m_length; // length of the buffer in bytes

    std::atomic_bool m_changed;
};

}; // namespace ux
