#include <ncurses++/color_rect.hpp>
#include <ncurses++/drawing.hpp>

namespace ncursespp
{

void color_rect::redraw(rect_i r)
{
    draw::fill_rect(r, color_);
}

} // namespace ncursespp
