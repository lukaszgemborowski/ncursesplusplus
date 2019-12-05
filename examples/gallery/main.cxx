#include <ncurses++/vsplit.hpp>
#include <ncurses++/hsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/text.hpp>
#include <ncurses++/text_list.hpp>
#include <ncurses++/palette.hpp>

int main()
{
    using namespace ncursespp;
    session sess;

    auto pal = palette {
        color_pair{1_idx, color::black, color::white},
        color_pair{2_idx, color::black, color::yellow},
        color_pair{5_idx, color::black, color::blue},
        color_pair{3_idx, color::yellow, color::green},
        color_pair{4_idx, color::blue, color::magenta},
        color_pair{6_idx, color::black, color::green}
    };

    auto hs = hsplit {
        constraint::fixed<15> {},
        std::forward_as_tuple(
            color_rect{constraint::fixed<4>{}, pal.get(1_idx)},
            color_rect{constraint::fill{}, pal.get(2_idx)}
        )
    };

    auto list = text_list {constraint::fill{}, 3, 4, 6};
    list.append("foo1");
    list.append("foo2");
    list.append("foo3");
    list.append("foo4");
    list.append("foo5");

    auto vs = vsplit {
        constraint::fill {},
        std::forward_as_tuple(
            hs,
            color_rect{constraint::fixed<3>{}, pal.get(5_idx)},
            list
        )
    };

    vs.resize(sess.size());

    sess.refresh();

    int c = 0;
    int idx = 0;
    list.select(idx);

    while (c != 'q') {
        c = sess.getkey();

        if (c == 's') {
            idx ++;
        } else if (c == 'w') {
            idx --;
        }

        list.select(idx);
        vs.resize(sess.size());
    }

    return 0;
}
