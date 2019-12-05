#ifndef NCURSES_TEXT_LIST_HPP
#define NCURSES_TEXT_LIST_HPP

#include <ncurses++/color.hpp>
#include <ncurses++/rect.hpp>
#include <ncurses++/constraints.hpp>
#include <ncurses++/widget.hpp>
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
    text_list_base(short c1, short c2, short s);

    void append(std::string item);
    void append(std::initializer_list<std::string> items);
    void select(int idx);
    int selected() const;

    void do_resize(rect_i r);

private:
    void draw_one(rect_i r, int line) const;

private:
    short color1_;
    short color2_;
    short colorHighlight_;
    std::vector<std::string> items_;
    int selected_;
    int displayPosition_;
};

} // namespace detail

template<class Size = constraint::fill>
class text_list : public detail::text_list_base
{
public:
    using constraint_t = Size;

    text_list(Size, short c1, short c2, short s)
        : text_list_base{c1, c2, s}
    {}
};

} // namespace ncirsespp

#endif // NCURSES_TEXT_LIST_HPP
