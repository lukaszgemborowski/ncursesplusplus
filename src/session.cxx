#include "ncurses++/session.hpp"
#include <ncurses.h>
#include <cassert>

namespace ncursespp
{

session::session()
{
    assert(initscr() != nullptr);
    cbreak();
    noecho();
    clear();
}

session::~session()
{
    endwin();
}

void session::refresh()
{
    ::refresh();
}

} // namespace ncursespp
