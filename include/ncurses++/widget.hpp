#ifndef NCURSESPP_WIDGET_HPP
#define NCURSESPP_WIDGET_HPP

#include <ncurses++/rect.hpp>

namespace ncursespp
{

template<class Base>
class widget
{
public:
    widget() = default;

    void resize(rect_i r)
    {
        static_cast<Base *>(this)->do_resize (r);
        size_ = r;
    }

    constexpr auto size() const
    {
        return size_;
    }

private:
    rect_i size_;
};

} // namespace ncursespp

#endif // NCURSESPP_WIDGET_HPP
