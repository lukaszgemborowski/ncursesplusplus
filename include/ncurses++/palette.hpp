#ifndef NCURSESPP_PALETTE_HPP
#define NCURSESPP_PALETTE_HPP

#include <ncurses++/color.hpp>
#include <initializer_list>
#include <tuple>

namespace ncursespp
{

template<int I>
struct color_pair
{
    template<int Index>
    constexpr color_pair(
            std::integral_constant<int, Index>,
            color FG,
            color BG
        )
        : fg {FG}
        , bg {BG}
    {}

    static constexpr int pair = I;
    color fg;
    color bg;
};

template<class IntConst>
color_pair(IntConst, color, color) -> color_pair<IntConst::value>;

constexpr int accumulate_chars(std::initializer_list<char> chs)
{
    int res = 0;
    for (const auto &c : chs)
        res += ((res * 10) + (c - '0'));
    return res;
}

template<char... C>
constexpr auto operator"" _idx ()
{
    return std::integral_constant<int, accumulate_chars({C...})>{};
}

namespace detail
{

struct palette_base
{
protected:
    palette_base();

    static void init_pair(short pair, color f, color b);

private:
    static bool initialized;
};

} // namespace detail

template<class... Pairs>
struct palette : detail::palette_base
{
    palette(Pairs... p)
        : pairs {p...}
    {
        (do_init(p), ...);
    }

    template<class Pair>
    void do_init(Pair p)
    {
        palette_base::init_pair(p.pair, p.fg, p.bg);
    }

    template<class Pair>
    constexpr short get(Pair p) const
    {
        return p.value;
    }

private:
    std::tuple<Pairs...> pairs;
};

} // namespace ncurses

#endif // NCURSESPP_PALETTE_HPP
