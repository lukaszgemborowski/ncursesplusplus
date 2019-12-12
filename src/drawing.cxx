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

int draw::text(const std::string &text, rect_i r, short color)
{
    auto lt = r.left_top;
    int res = 0;
    fill_rect(r, color); // TODO: optimize!

    attron(COLOR_PAIR(color));
    for (auto i = 0u;
         static_cast<int>(i) < r.width() && i < text.size();
         ++i) {
        mvaddch(lt.y, lt.x + i, text[i]);
        res ++;
    }
    attroff(COLOR_PAIR(color));
    return res;
}

} // namespace ncursespp
