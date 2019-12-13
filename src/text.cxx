#include <ncurses++/text.hpp>
#include <ncurses++/drawing.hpp>
#include <ncurses.h>

namespace ncursespp
{

void text::do_resize(rect_i r)
{
    auto lt = r.left_top;
    auto width = r.width();

    attron(COLOR_PAIR(color_));

    draw::fill_rect(r, color_);

    for (auto x = 0; x < width && static_cast<std::size_t>(x) < text_.size(); ++x) {
        mvaddch(lt.y, x + lt.x, text_[x]);
    }

    attroff(COLOR_PAIR(color_));
}

} // namespace ncurses
