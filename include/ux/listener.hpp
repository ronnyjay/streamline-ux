#pragma once

#include <any>
#include <functional>
#include <string>
#include <unordered_map>

namespace ux
{

class listener
{
  public:
    listener()
    {
    }

    listener(const listener &ref)
    {
        if (this != &ref)
        {
            m_events = ref.m_events;
        }
    }

    listener &operator=(const listener &ref)
    {
        if (this != &ref)
        {
            m_events = ref.m_events;
        }

        return *this;
    }

    template <typename callback> void on(std::basic_string<char> e, callback &&_callback)
    {
        m_events[e] = std::any(std::function(std::forward<callback>(_callback)));
    }

    template <typename val, typename... args> val emit(std::basic_string<char> e, args &&..._args)
    {
        if (m_events.find(e) == m_events.end())
        {
            return;
        }

        return std::any_cast<std::function<val(args...)> &>(m_events[e])(
            std::forward<args>(_args)...);
    }

  private:
    std::unordered_map<std::basic_string<char>, std::any> m_events;
};

}; // namespace ux