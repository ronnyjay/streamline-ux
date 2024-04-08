#pragma once

#include <ux/widget.hpp>

#include <chrono>

namespace ux
{

class animation : public widget
{

  public:
    animation(const int, const int, const int, const int);

    void enable();
    void disable();

    virtual const bool finished();
    virtual void restart();

    const int get_frame();
    void set_frame(const int);

    const speed get_speed();
    void set_speed(const speed);

    const color foreground();
    const color background();

  protected:
    virtual void execute_action() override;

    std::chrono::system_clock::time_point m_last_updated;

  private:
    int m_frame;

    color m_foreground;
    color m_background;

    speed m_speed;
};

class loading_bar : public animation
{
  public:
    loading_bar(const int, const int, const int, const int);

    virtual void resize(const int, const int) override;
    virtual void display() override;
    virtual const bool finished() override;

  private:
    std::basic_string<wchar_t> m_bar;
};

class ticker : public animation
{
  public:
    ticker(const int, const int, const int, const int);

    virtual void display() override;

    virtual const bool finished() override;
    virtual void restart() override;

    void set_text(std::basic_string<char>);

    const int get_cursor();
    void set_cursor(const int);

    const bool colliding();
    const bool out_of_range();

  private:
    int m_cursor;

    std::basic_string<char> m_text;
};

}; // namespace ux