#include <ux/renderer.hpp>

#include <csignal>
#include <stdexcept>

using namespace ux;

extern volatile std::atomic_bool running;

renderer::renderer()
{
    std::signal(SIGWINCH, NULL);

    initscr();
    noecho();
    cbreak();
    setlocale(LC_ALL, ""); // unicode support

    getmaxyx(stdscr, m_height, m_width);

    if (!has_colors())
    {
        endwin();

        throw std::runtime_error("Terminal is missing color support");
    }

    start_color();

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_BLACK);
}

void renderer::add_widget(widget *widget)
{
    std::unique_lock<std::mutex> guard(m_lock);

    m_widgets.emplace_back(widget);
}

void renderer::start()
{
    m_handle = std::thread(&renderer::handle, this);
}

void renderer::end()
{
    std::unique_lock<std::mutex> guard(m_lock);

    if (m_handle.joinable())
    {
        m_handle.join();
    }

    m_widgets.clear();

    endwin();
}

void renderer::handle()
{
    bool resized;

    while (running)
    {
        std::unique_lock<std::mutex> guard(m_lock);

        resized = false;

        if (is_term_resized(m_height, m_width))
        {
            werase(stdscr);
            wrefresh(stdscr);

            resized = true;

            getmaxyx(stdscr, m_height, m_width);
        }

        for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); ++it)
        {
            auto &widget = *it;

            if (resized)
            {
                widget->emit<void>("resize");
                widget->set_updated(true);
            }

            switch (widget->get_status())
            {
            case idle:
                break;
            case active:
                widget->execute_action();
                break;
            case complete:
                widget->set_status(idle);
                break;
            }

            if (widget->updated())
            {
                widget->display();
                widget->set_updated(false);
            }
        }

        resized = false;
    }
}
