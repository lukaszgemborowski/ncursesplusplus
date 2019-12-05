#ifndef NCURSESPP_CONSTRAINTS_HPP
#define NCURSESPP_CONSTRAINTS_HPP

#include <type_traits>

namespace ncursespp
{
namespace constraint
{

template<int Size>
struct fixed : std::integral_constant<int, Size> {
};

struct fill {
};

template<class>
struct size_calculator;

template<int Size>
struct size_calculator<fixed<Size>>
{
    static constexpr int calc(int &space)
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
};

template<>
struct size_calculator<fill>
{
    static constexpr int calc(int &)
    {
        return -1;
    }
};

} // namespace constraint
} // namespace ncursespp

#endif // NCURSESPP_CONSTRAINTS_HPP
