#include <ncurses++/drawing.hpp>
#include <ncurses.h>

namespace ncursespp
{

void draw::fill_rect(rect_i r, short color)
{
    auto lt = r.left_top;
    auto rb = r.right_bottom;

    attron(COLOR_PAIR(color));

    for (int x = lt.x; x <= rb.x; ++x) {
        for (int y = lt.y; y <= rb.y; ++y) {
            mvaddch(y, x, ' ');
        }
    }

    attroff(COLOR_PAIR(color));
}

} // namespace ncursespp
