#ifndef NCURSESPP_DRAWING_HPP
#define NCURSESPP_DRAWING_HPP

#include <ncurses++/rect.hpp>

namespace ncursespp
{

struct draw
{
    static void fill_rect(rect_i r, short color);
    static void text(const std::string &text, rect_i r, short color);
};

} // namespace ncursespp

#endif // NCURSESPP_DRAWING_HPP
