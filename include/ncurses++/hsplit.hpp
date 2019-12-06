#ifndef NCURSESPP_HSPLIT_HPP
#define NCURSESPP_HSPLIT_HPP

#include <ncurses++/rect.hpp>
#include <ncurses++/constraints.hpp>
#include <type_traits>
#include <array>

namespace ncursespp
{

// TODO: commonize code from hsplit and vsplit
template<class... Collection>
class hsplit
{
public:
    static constexpr auto count = sizeof...(Collection);

    hsplit(Collection&&... splits)
        : splits {std::move(splits)...}
    {}

    void resize(rect_i size)
    {
        resize_impl(
            size,
            std::make_index_sequence<count>{}
        );
    }

private:
    template<std::size_t... I>
    void resize_impl(rect_i size, std::index_sequence<I...>)
    {
        std::array<int, count> widths {};
        int idx = 0;
        auto space = size.height();

        // query size_calculator<>::calc for every constraint_t in Splits
        // calc will decrement space when the size is known
        auto apply_calc = [&](auto& S) {
            using SplitType = std::decay_t<decltype(S)>;
            widths[idx] = SplitType::calc(space);
            idx ++;
        };

        (apply_calc(std::get<I>(splits)), ...);

        idx = 0;
        int ypos = 0;
        auto apply_resize = [&](auto& S) {
            if (widths[idx] == -1 && space > 0) {
                auto r = rect_i{{size.left_top.x, ypos}, {size.right_bottom.x, ypos + space}};
                ypos += space;
                space = 0;
                S.resize(r);

            } else if (widths[idx] > 0) {
                auto r = rect_i{{size.left_top.x, ypos}, {size.right_bottom.x, ypos + widths[idx]}};
                ypos += widths[idx];
                S.resize(r);
            }

            idx ++;
        };

        (apply_resize(std::get<I>(splits)), ...);
    }

private:
    std::tuple<Collection...> splits;
};

} // namespace ncursespp

#endif // NCURSESPP_HSPLIT_HPP
