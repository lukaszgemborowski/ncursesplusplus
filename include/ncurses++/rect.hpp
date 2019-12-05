#ifndef NCURSESPP_RECT_HPP
#define NCURSESPP_RECT_HPP

#ifndef NDEBUG
    #include <iostream>
#endif

namespace ncursespp
{

template<class T>
struct point
{
    point (T x, T y)
        : x {x}
        , y {y}
    {}

    T x;
    T y;
};

template<class T>
struct rect
{
    rect(point<T> left_top, point<T> right_bottom)
        : left_top {left_top}
        , right_bottom {right_bottom}
    {
    }

    point<T> left_top;
    point<T> right_bottom;

    constexpr auto width() const
    {
        return right_bottom.x - left_top.x;
    }

    constexpr auto height() const
    {
        return right_bottom.y - left_top.y;
    }
};

#ifndef NDEBUG
template<class T>
std::ostream& operator << (std::ostream& os, ncursespp::rect<T> &r)
{
    os << "r{{" << r.left_top.x << ", " << r.left_top.y << "}, {" <<
            r.right_bottom.x << ", " << r.right_bottom.y << "}}";
    return os;
}
#endif // !NDEBUG

using rect_i = rect<int>;

} // namespace ncursespp

#endif // NCURSESPP_RECT_HPP
