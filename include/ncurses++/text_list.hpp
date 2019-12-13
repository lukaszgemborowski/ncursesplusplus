#ifndef NCURSES_TEXT_LIST_HPP
#define NCURSES_TEXT_LIST_HPP

#include <ncurses++/color.hpp>
#include <ncurses++/rect.hpp>
#include <ncurses++/constraints.hpp>
#include <ncurses++/widget.hpp>
#include <ncurses++/palette.hpp>
#include <string>
#include <vector>
#include <initializer_list>

namespace ncursespp
{
namespace detail
{
class text_list_base : public widget<text_list_base>
{
public:
    text_list_base(color_index c1, color_index c2, color_index s);

    void append(std::string item);
    void append(std::initializer_list<std::string> items);
    void select(int idx);
    int selected() const;

    void do_resize(rect_i r);

private:
    void draw_one(rect_i r, int line) const;

private:
    color_index color1_;
    color_index color2_;
    color_index colorHighlight_;
    std::vector<std::string> items_;
    int selected_;
    int displayPosition_;
};

} // namespace detail

class text_list : public detail::text_list_base
{
public:
    text_list(color_index c1, color_index c2, color_index s)
        : text_list_base{c1, c2, s}
    {}
};

} // namespace ncirsespp

#endif // NCURSES_TEXT_LIST_HPP
