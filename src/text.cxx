#include <ncurses++/text.hpp>
#include <ncurses++/drawing.hpp>
#include <ncurses.h>

namespace ncursespp
{

void text::do_resize(rect_i r)
{
    draw::fill_rect(r, color_);

    auto p = r.left_top;
    auto i = 0u;
    attron(COLOR_PAIR(color_));

    while (text_[i] != '\0') {
        if (p.y > r.right_bottom.y) {
            break;
        }

        if (text_[i] == '\n') {
            p.x = r.left_top.x;
            p.y ++;
            i ++;
            continue;
        }

        if (p.x > r.right_bottom.x) {
            i ++;
            continue;
        }

        mvaddch(p.y, p.x, text_[i]);
        i ++;
        p.x ++;
    }

    attroff(COLOR_PAIR(color_));
}

} // namespace ncurses
