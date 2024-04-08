#pragma once

#include <ux/widget.hpp>

#include <list>

#define TAG_PADDING 4
namespace ux
{

class log : public widget
{
  public:
    log(const int, const int, const int, const int);

    virtual void display() override;

    void insert(decorated_string, std::basic_string<char>);

  private:
    std::list<std::pair<decorated_string, std::basic_string<char>>> m_entries;
};

}; // namespace ux