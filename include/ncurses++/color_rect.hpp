#ifndef NCURSESPP_COLOR_RECT_HPP
#define NCURSESPP_COLOR_RECT_HPP

#include <ncurses++/color.hpp>
#include <ncurses++/rect.hpp>
#include <ncurses++/constraints.hpp>
#include <type_traits>
#include <algorithm>

namespace ncursespp
{

namespace detail
{
struct color_rect_base
{
    color_rect_base(short c)
        : color_ {c}
    {}

    void redraw(rect_i r);
    short color_;
};
} // detail

class color_rect : public detail::color_rect_base
{
public:
    color_rect(short c)
        : color_rect_base {c}
    {}

    void resize(rect_i r)
    {
        color_rect_base::redraw(r);
    }

private:
};

} // namespace ncursespp

#endif // NCURSESPP_COLOR_RECT_HPP
