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

    void draw_one(rect_i r, int itemIndex, int y_pos) const
    {
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
                {x1, y + y_pos},
                {x2, y + y_pos + item.height()}
            }
        );
    }

    void do_resize(rect_i r)
    {
        auto visibleItems = visible_items(r.height());
        auto y_pos = 0;
        auto itemIndex = displayPosition_;

        for (int i = 0; i < visibleItems; i++, itemIndex ++) {
            draw_one(r, itemIndex, y_pos);
            y_pos += items_[itemIndex].height();
        }
    }

    void select(int idx)
    {
        if (idx < 0 || idx >= items_.size())
            return;

        auto visibleItems = visible_items();
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

    void select_up()
    {
        select(selected_index() - 1);
    }

    void select_down()
    {
        select(selected_index() + 1);
    }

    auto& selected()
    {
        return items_[selected_index()];
    }

    auto selected_index() const
    {
        return selected_;
    }

    void append(Item &&item)
    {
        items_.emplace_back (std::move(item));
    }

private:
    auto visible_items() const
    {
        return visible_items(size().height());
    }

    auto visible_items(int current_height) const
    {
        auto cumulative = 0;
        auto count = 0;

        for (auto i = displayPosition_;
             i < items_.size();
             i ++)
        {
            cumulative += items_[i].height();

            if (cumulative <= current_height) {
                ++ count;
            } else {
                break;
            }
        }

        return count;
    }

private:
    std::vector<Item> items_;
    int selected_;
    int displayPosition_;
};

} // namespace ncursespp

#endif // NCURSESPP_ITEM_LIST_HPP
