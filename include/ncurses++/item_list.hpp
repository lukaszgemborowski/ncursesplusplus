#ifndef NCURSESPP_ITEM_LIST_HPP
#define NCURSESPP_ITEM_LIST_HPP

#include <ncurses++/constraints.hpp>
#include <ncurses++/widget.hpp>
#include <vector>

namespace ncursespp
{

template<class Item>
class item_list : public widget<item_list<Item>>
{
public:
    item_list()
        : selected_ {-1}
        , displayPosition_ {0}
    {}

    auto size() const
    {
        return widget<item_list<Item>>::size();
    }

    void draw_one(rect_i r, int line) const
    {
        auto itemIndex = line + displayPosition_;
        auto x1 = r.left_top.x;
        auto x2 = r.right_bottom.x;
        auto y  = r.left_top.y;

        if (itemIndex >= items_.size())
            return;

        auto &item = items_[itemIndex];
        item.draw(
            itemIndex,
            itemIndex == selected_,
            rect_i {
                {x1, y + (Item::height * line)},
                {x2, y + (Item::height * (line + 1)) - 1}
            }
        );
    }

    void do_resize(rect_i r)
    {
        auto visibleItems = size().height() / Item::height;

        for (int i = 0; i < visibleItems; i++) {
            draw_one(r, i);
        }
    }

    void select(int idx)
    {
        if (idx < 0 || idx >= items_.size())
            return;

        auto visibleItems = size().height() / Item::height;
        auto lastVisible = displayPosition_ + visibleItems - 1;

        selected_ = idx;

        if (idx < displayPosition_) {
            displayPosition_ = idx;
        } else if (idx > lastVisible) {
            displayPosition_ = (idx - visibleItems) + 1;
        }

        // TODO: else, can be optimized, only two lines
        // could be redrawn
        do_resize(size());
    }

    auto selected() const
    {
        return selected_;
    }

    void append(Item &&item)
    {
        items_.emplace_back (std::move(item));
    }

private:
    std::vector<Item> items_;
    int selected_;
    int displayPosition_;
};

} // namespace ncursespp

#endif // NCURSESPP_ITEM_LIST_HPP
