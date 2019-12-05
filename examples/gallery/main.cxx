#include <ncurses++/vsplit.hpp>
#include <ncurses++/hsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/text.hpp>
#include <ncurses++/text_list.hpp>
#include <ncurses++/palette.hpp>

#include <sstream>

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

int main()
{
    using namespace ncursespp;
    session sess;

    auto pal = create_palette();

    auto list = text_list {constraint::fixed<5>{}, 3, 4, 6};

    auto left_panel = hsplit {
        constraint::fixed<20>{},
        std::forward_as_tuple(
            list,
            color_rect{constraint::fill{}, 1}
        )
    };

    auto vs = vsplit {
        constraint::fill {},
        std::forward_as_tuple(
            left_panel,
            color_rect{constraint::fixed<1>{}, 5},
            color_rect{constraint::fill{}, 1}
        )
    };

    for (int i = 0; i < 10; i ++) {
        std::stringstream ss;
        ss << "text " << i;
        list.append(ss.str());
    }

    vs.resize(sess.size());
    sess.refresh();

    int c = 0;
    list.select(0);

    while (c != 'q') {
        c = sess.getkey();

        if (c == 's') {
            list.select(list.selected() + 1);
        } else if (c == 'w') {
            list.select(list.selected() - 1);
        }
    }

    return 0;
}
