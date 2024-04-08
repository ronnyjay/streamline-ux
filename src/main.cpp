#include <ux/animation.hpp>
#include <ux/common.hpp>
#include <ux/dashboard.hpp>
#include <ux/input.hpp>
#include <ux/log.hpp>
#include <ux/renderer.hpp>
#include <ux/widget.hpp>

#include <csignal>

#define DASHBOARD_WIDTH 31

volatile std::atomic_bool running = true;

void signal_handler(int sig)
{
    running = false;
}

int main(int argc, char const *argv[])
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGALRM, signal_handler);
    std::signal(SIGPIPE, SIG_IGN);
    std::signal(SIGUSR1, SIG_IGN);
    std::signal(SIGUSR2, SIG_IGN);

    ux::renderer renderer;

    ux::dashboard dashboard(SCREEN_HEIGHT, DASHBOARD_WIDTH, SCREEN_TOP, SCREEN_WIDTH - DASHBOARD_WIDTH);
    ux::input input(1, SCREEN_WIDTH - DASHBOARD_WIDTH, SCREEN_BOTTOM, SCREEN_LEFT);
    ux::input prompt(3, 32, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 16);
    ux::log log(SCREEN_HEIGHT - 4, SCREEN_WIDTH - DASHBOARD_WIDTH, SCREEN_TOP + 3, SCREEN_LEFT);

    ux::loading_bar loading_animation(3, 32, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 16);
    ux::ticker ticker_animation(3, COLS - DASHBOARD_WIDTH, 0, 0);

    dashboard.on_resize(
        [&dashboard]()
        {
            dashboard.resize(SCREEN_HEIGHT, DASHBOARD_WIDTH);
            dashboard.position(SCREEN_TOP, SCREEN_WIDTH - DASHBOARD_WIDTH);
        });

    input.on_resize(
        [&input]()
        {
            input.resize(1, SCREEN_WIDTH - DASHBOARD_WIDTH);
            input.position(SCREEN_BOTTOM, SCREEN_LEFT);
        });

    prompt.on_resize(
        [&prompt]()
        {
            prompt.resize(3, 32);
            prompt.position(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 16);
        });

    log.on_resize(
        [&log]()
        {
            log.resize(SCREEN_HEIGHT - 4, SCREEN_WIDTH - DASHBOARD_WIDTH);
            log.position(SCREEN_TOP + 3, SCREEN_LEFT);
        });

    loading_animation.on_resize(
        [&loading_animation]()
        {
            loading_animation.resize(3, 32);
            loading_animation.position(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 16);
        });

    ticker_animation.on_resize(
        [&ticker_animation]()
        {
            ticker_animation.resize(3, SCREEN_WIDTH - DASHBOARD_WIDTH);
            ticker_animation.position(0, 0);
        });

    dashboard.set_border(true);
    dashboard.add_table("rooms");
    dashboard.add_table("users");

    input.show_character_count(true);
    input.prefix().set_segment(1, "@streamlinechat > ", ux::white, ux::bold);

    prompt.set_border(true);
    prompt.show_character_count(true);

    renderer.add_widget(&dashboard);
    renderer.add_widget(&input);
    renderer.add_widget(&prompt);
    renderer.add_widget(&log);
    renderer.add_widget(&loading_animation);
    renderer.add_widget(&ticker_animation);
    renderer.start();

    while (running)
    {
        std::basic_string<char> str = input.read_line();

        if (!str.compare("/exit"))
        {
            running = false;
            break;
        }

        if (str.length())
        {
            log.insert(ux::decorated_string("ronny", ux::magenta), str);
        }
    }

    renderer.end();

    return 0;
}
