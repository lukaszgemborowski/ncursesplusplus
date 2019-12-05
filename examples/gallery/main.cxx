#include <ncurses++/vsplit.hpp>
#include <ncurses++/hsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>

#include <ncurses++/palette.hpp>

#include <unistd.h> // pause()

int main()
{
    using namespace ncursespp;
    session sess;

    auto pal = palette {
        color_pair{1_idx, color::red, color::white},
        color_pair{2_idx, color::black, color::yellow},
        color_pair{3_idx, color::red, color::red}
    };

    auto hs = hsplit {
        constraint::fixed<15> {},
        std::make_tuple(
            color_rect{constraint::fixed<2>{}, pal.get(1_idx)},
            color_rect{constraint::fill{}, pal.get(2_idx)}
        )
    };

    auto vs = vsplit {
        constraint::fill {},
        std::make_tuple(
            hs,
            color_rect{constraint::fill{}, pal.get(3_idx)}
        )
    };

    vs.resize(rect_i{{0, 0}, {40, 25}});

    sess.refresh();

    pause();
    return 0;
}
