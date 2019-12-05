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

rect_i session::size() const
{
    int x = 0, y = 0;

    getmaxyx(stdscr, y, x);

    return {{0, 0}, {x, y}};
}

int session::getkey() const
{
    return ::getch();
}

} // namespace ncursespp
