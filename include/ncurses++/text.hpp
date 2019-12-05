#ifndef NCURSESPP_TEXT_HPP
#define NCURSESPP_TEXT_HPP

#include <ncurses++/rect.hpp>
#include <string>

namespace ncursespp
{
namespace detail
{

class text_base
{
public:
    text_base(std::string text, short c)
        : text_ {std::move(text)}
        , color_ {c}
    {}

    void resize(rect_i r);

private:
    std::string text_;
    short color_;
};

} // namespace detail

template<class Size>
class text : public detail::text_base
{
public:
    using constraint_t = Size;

    text(Size, std::string text, short c)
        : text_base {std::move(text), c}
    {
    }

private:
};

} // namespace ncursespp

#endif // NCURSESPP_TEXT_HPP
