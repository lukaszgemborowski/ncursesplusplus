#include <ncurses++/vsplit.hpp>
#include <ncurses++/hsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/text.hpp>
#include <ncurses++/text_list.hpp>
#include <ncurses++/palette.hpp>
#include <ncurses++/item_list.hpp>
#include <ncurses++/drawing.hpp>

#include <sstream>

struct empty_item {
    constexpr auto height() const
    {
        return 3;
    }

    void draw(int line, bool selected, ncursespp::rect_i r) const
    {
        using namespace ncursespp;

        auto color = line % 2_idx ? 1_idx : 2_idx;
        color = selected ? 3_idx : color;

        ncursespp::draw::fill_rect(r, color);
    }
};

auto create_palette()
{
    using namespace ncursespp;
    return palette {
        color_pair{1_idx, color::black  , color::white},
        color_pair{2_idx, color::black  , color::yellow},
        color_pair{5_idx, color::black  , color::blue},
        color_pair{3_idx, color::yellow , color::green},
        color_pair{4_idx, color::blue   , color::magenta},
        color_pair{6_idx, color::black  , color::green}
    };
}

std::string generate_text()
{
    return R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. In laoreet, arcu ut porttitor viverra, massa libero molestie
risus, vel commodo lorem velit sed ex. Cras porta neque id)";
}

int main()
{
    using namespace ncursespp;
    namespace ct = constraint;
    session sess;

    auto pal = create_palette();
    pal.redefine(color::white, 500, 0, 0);
    pal.apply();
    auto list = item_list<empty_item> {};

    auto left_panel = hsplit {
        ct::fixed<15>(list),
        ct::fill(color_rect{5_idx})
    };

    auto vs = vsplit {
        ct::fixed<20>(left_panel),
        ct::fixed<1>(color_rect{5_idx}),
        ct::fill(text{generate_text(), 1_idx})
    };

    for (int i = 0; i < 10; i ++) {
        list.append(empty_item{});
    }

    vs.resize(sess.size());
    sess.refresh();

    int c = 0;
    list.select(0);

    while (c != 'q') {
        c = sess.getkey();

        if (c == 's') {
            list.select_down();
        } else if (c == 'w') {
            list.select_up();
        }
    }

    return 0;
}
