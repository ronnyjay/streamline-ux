#pragma once

#include <ux/buffer.hpp>
#include <ux/common.hpp>
#include <ux/listener.hpp>

#include <atomic>

#define BORDER_OFFSET (has_border() ? 1 : 0)

namespace ux
{

class widget
{
  public:
    widget(const int, const int, const int, const int);
    virtual ~widget();

    virtual void resize(const int, const int);
    virtual void position(const int, const int);

    virtual void refresh();

    virtual void display()
    {
    }

    virtual void execute_action()
    {
    }

    void move_cursor_to(const int, const int);

    virtual const bool updated();
    virtual void set_updated(const bool);

    const status get_status();
    void set_status(const status);

    const bool hidden();
    void set_hidden(const bool);

    const bool has_border();
    void set_border(const bool);

    const int read_char();

    const int height();
    const int width();

    void box();

    void printline(const std::basic_string<char>);
    void printline(const std::basic_string<char>, const int, const int);
    void printline(const std::basic_string<char>, color, attribute);
    void printline(const std::basic_string<char>, const int, const int, color, attribute);
    void printline(const std::basic_string<wchar_t>);
    void printline(const std::basic_string<wchar_t>, const int, const int);
    void printline(const std::basic_string<wchar_t>, color, attribute);
    void printline(const std::basic_string<wchar_t>, const int, const int, color, attribute);

    void on_resize(std::function<void()>);

    template <typename val, typename... args> val emit(std::basic_string<char> e, args &&..._args)
    {
        return m_listener.emit<val>(e, std::forward<args>(_args)...);
    }

  private:
    WINDOW *m_window;

    std::atomic_bool m_updated;
    std::atomic_bool m_hidden;
    std::atomic_bool m_border;

    status m_status;

    listener m_listener;
};

}; // namespace ux