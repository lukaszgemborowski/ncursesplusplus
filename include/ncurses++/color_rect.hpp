#ifndef NCURSESPP_COLOR_RECT_HPP
#define NCURSESPP_COLOR_RECT_HPP

#include <ncurses++/rect.hpp>
#include <ncurses++/widget.hpp>
#include <ncurses++/palette.hpp>

namespace ncursespp
{

class color_rect : public widget<color_rect>
{
public:
    color_rect(color_index c)
        : color_ {c}
    {}

    void do_resize(rect_i r)
    {
        redraw(r);
    }

private:
    void redraw(rect_i r);
    color_index color_;
};

} // namespace ncursespp

#endif // NCURSESPP_COLOR_RECT_HPP
