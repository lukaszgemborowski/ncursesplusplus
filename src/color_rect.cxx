#include <ncurses++/color_rect.hpp>
#include <ncurses.h>

namespace ncursespp::detail
{

void color_rect_base::redraw(rect_i r)
{
    auto lt = r.left_top;
    auto rb = r.right_bottom;

    attron(COLOR_PAIR(color_));

    for (int x = lt.x; x <= rb.x; ++x) {
        for (int y = lt.y; y <= rb.y; ++y) {
            mvaddch(y, x, ' ');
        }
    }

    attroff(COLOR_PAIR(color_));
}

} // namespace ncursespp::detail
