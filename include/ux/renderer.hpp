#pragma once

#include <ux/buffer.hpp>
#include <ux/common.hpp>
#include <ux/widget.hpp>

#include <mutex>
#include <thread>

#define SCREEN_HEIGHT LINES
#define SCREEN_WIDTH COLS

#define SCREEN_TOP 0
#define SCREEN_BOTTOM LINES - 1

#define SCREEN_LEFT 0
#define SCREEN_RIGHT COLS - 1

namespace ux
{

class renderer
{
  public:
    renderer();

    void add_widget(widget *);

    void start();
    void end();

  private:
    std::atomic_int m_height;
    std::atomic_int m_width;

    std::thread m_handle;
    std::mutex m_lock;

    std::vector<widget *> m_widgets;

    void handle();
};

}; // namespace ux