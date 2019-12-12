#include <ncurses++/text.hpp>
#include <ncurses.h>

namespace ncursespp::detail
{

void text_base::do_resize(rect_i r)
{
    auto lt = r.left_top;
    auto rb = r.right_bottom;
    auto width = r.width();

    attron(COLOR_PAIR(color_));

    // draw background
    // TODO: this is basically code from color_rect, make it common?
    for (int x = lt.x; x <= rb.x; ++x) {
        for (int y = lt.y; y <= rb.y; ++y) {
            mvaddch(y, x, ' ');
        }
    }

    for (auto x = 0; x < width && static_cast<std::size_t>(x) < text_.size(); ++x) {
        mvaddch(lt.y, x + lt.x, text_[x]);
    }

    attroff(COLOR_PAIR(color_));
}

} // namespace ncurses::detail
