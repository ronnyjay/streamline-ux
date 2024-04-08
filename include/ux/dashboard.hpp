#pragma once

#include <ux/widget.hpp>

#include <map>

#define TABLE_PADDING 2

namespace ux
{

class dashboard : public widget
{
  public:
    dashboard(const int, const int, const int, const int);

    virtual void display() override;

    void add_table(std::basic_string<char>);
    void insert_into_table(std::basic_string<char>, std::basic_string<char>);
    void clear_table(std::basic_string<char>);

  private:
    std::map<std::basic_string<char>, std::vector<std::basic_string<char>>> m_tables;
};

}; // namespace ux