#ifndef NCURSESPP_DRAWING_HPP
#define NCURSESPP_DRAWING_HPP

#include <ncurses++/rect.hpp>
#include <ncurses++/attributes.hpp>
#include <ncurses++/palette.hpp>

namespace ncursespp
{

struct draw
{
    static void fill_rect(rect_i r, color_index color);
    static int text(const std::string &text, rect_i r, color_index color);
    static void attribute_on(attribute attr);
    static void attribute_off(attribute attr);
};

} // namespace ncursespp

#endif // NCURSESPP_DRAWING_HPP
