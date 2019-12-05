#include <ncurses++/vsplit.hpp>
#include <ncurses++/hsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/text.hpp>
#include <ncurses++/palette.hpp>

#include <unistd.h> // pause()

int main()
{
    using namespace ncursespp;
    session sess;

    auto pal = palette {
        color_pair{1_idx, color::black, color::white},
        color_pair{2_idx, color::black, color::yellow},
        color_pair{3_idx, color::yellow, color::green},
        color_pair{4_idx, color::blue, color::magenta}
    };

    auto hs = hsplit {
        constraint::fixed<15> {},
        std::make_tuple(
            color_rect{constraint::fixed<2>{}, pal.get(1_idx)},
            color_rect{constraint::fill{}, pal.get(2_idx)}
        )
    };

    auto items = hsplit {
        constraint::fill {},
        std::make_tuple(
            text{constraint::fixed<1>{}, "foo1", 3},
            text{constraint::fixed<1>{}, "foo2", 4},
            text{constraint::fixed<1>{}, "foo3", 3},
            text{constraint::fixed<1>{}, "foo4", 4}
        )
    };

    auto vs = vsplit {
        constraint::fill {},
        std::make_tuple(
            hs,
            items
        )
    };

    vs.resize(sess.size());

    sess.refresh();

    pause();
    return 0;
}
