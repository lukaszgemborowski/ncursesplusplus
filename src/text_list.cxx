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
    , displayPosition_ {0}
{
}

void text_list_base::draw_one(rect_i r, int line) const
{
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

    auto textIndex = line + displayPosition_;

    if (textIndex >= items_.size())
        return;

    text_base t{items_[textIndex], color(textIndex)};
    t.resize(
        rect_i {
            {x, y + line}, {x2, y + line}
        }
    );
}

void text_list_base::do_resize(rect_i r)
{
    auto h = r.height();

    for (int line = 0; line <= h; ++line) {
        draw_one(r, line);
    }
}

void text_list_base::append(std::string item)
{
    items_.emplace_back(std::move(item));
}

void text_list_base::append(std::initializer_list<std::string> items)
{
    for (auto &e : items) {
        items_.emplace_back(std::move(e));
    }
}

void text_list_base::select(int idx)
{
    if (idx < 0 || idx >= items_.size())
        return;

    auto lastVisible = displayPosition_ + size().height();
    selected_ = idx;

    if (idx < displayPosition_) {
        displayPosition_ = idx;
    } else if (idx > lastVisible) {
        displayPosition_ = idx - size().height();
    }

    // TODO: else, can be optimized, only two lines
    // could be redrawn

    do_resize(size());
}

int text_list_base::selected() const
{
    return selected_;
}

} // namespace ncurses::detail
