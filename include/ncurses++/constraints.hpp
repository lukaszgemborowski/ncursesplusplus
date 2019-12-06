#ifndef NCURSESPP_CONSTRAINTS_HPP
#define NCURSESPP_CONSTRAINTS_HPP

#include <type_traits>

namespace ncursespp
{
namespace constraint
{

template<int Size, class Widget>
struct fixed_impl
{
    fixed_impl(Widget &w)
        : widget {std::move(w)}
    {}

    fixed_impl(Widget &&w)
        : widget {std::move(w)}
    {}

    // widget interface
    void resize(rect_i r) { widget.resize(r); }
    constexpr auto size() const { return widget.size(); }

    static constexpr auto calc(int &space)
    {
        if (space > Size) {
            space -= Size;
            return Size;
        } else {
            int t = space;
            space = 0;
            return t;
        }
    }

    Widget &&widget;
};

template<int Size, class Widget>
auto fixed(Widget &&widget)
{
    return fixed_impl<Size, std::decay_t<Widget>>{std::move(widget)};
}

template<class Widget>
struct fill_impl
{
    fill_impl(Widget &w)
        : widget {std::move(w)}
    {}

    fill_impl(Widget &&w)
        : widget {std::move(w)}
    {}

    // widget interface
    void resize(rect_i r) { widget.resize(r); }
    constexpr auto size() const { return widget.size(); }

    static constexpr auto calc(int &)
    {
        return -1;
    }

    Widget &&widget;
};

template<class Widget>
auto fill(Widget &&widget)
{
    return fill_impl<std::decay_t<Widget>>{std::move(widget)};
}

} // namespace constraint
} // namespace ncursespp

#endif // NCURSESPP_CONSTRAINTS_HPP
