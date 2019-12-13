#ifndef NCURSESPP_TEXT_HPP
#define NCURSESPP_TEXT_HPP

#include <ncurses++/rect.hpp>
#include <ncurses++/widget.hpp>
#include <string>

namespace ncursespp
{

class text : public widget<text>
{
public:
    text(std::string text, short c)
        : text_ {std::move(text)}
        , color_ {c}
    {
    }

    void do_resize(rect_i r);

private:
    std::string text_;
    short color_;
};

} // namespace ncursespp

#endif // NCURSESPP_TEXT_HPP
