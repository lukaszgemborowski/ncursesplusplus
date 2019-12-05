#include <ncurses++/text_list.hpp>
#include <ncurses++/text.hpp>

namespace ncursespp::detail
{

text_list_base::text_list_base(short c1, short c2, short s)
    : color1_ {c1}
    , color2_ {c2}
    , colorHighlight_ {s}
    , items_ {}
    , selected_ {-1}
{
}

void text_list_base::resize(rect_i r)
{
    auto h = r.height();
    auto x = r.left_top.x;
    auto y = r.left_top.y;
    auto x2 = r.right_bottom.x;

    auto color = [this](int n) {
        if (n == selected_)
            return colorHighlight_;
        if (n & 1)
            return color1_;
        else
            return color2_;
    };

    for (int line = 0; line < h && line < items_.size(); ++line) {
        text_base t{items_[line], color(line)};
        t.resize(
            rect_i {
                {x, y + line}, {x2, y + line}
            }
        );
    }
}

void text_list_base::append(std::string item)
{
    items_.emplace_back(std::move(item));
}

void text_list_base::select(int idx)
{
    selected_ = idx;
}

} // namespace ncurses::detail
