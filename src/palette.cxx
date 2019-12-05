#include <ncurses++/palette.hpp>
#include <ncurses.h>
#include <cassert>

namespace
{
constexpr short color_enum_to_ncurses(ncursespp::color c)
{
    using namespace ncursespp;

    switch (c) {
        case color::black: return COLOR_BLACK;
        case color::red: return COLOR_RED;
        case color::green: return COLOR_GREEN;
        case color::yellow: return COLOR_YELLOW;
        case color::blue: return COLOR_BLUE;
        case color::magenta: return COLOR_MAGENTA;
        case color::cyan: return COLOR_CYAN;
        case color::white: return COLOR_WHITE;
    };
}
}

namespace ncursespp
{
namespace detail
{

bool palette_base::initialized = false;

palette_base::palette_base()
{
    if (!initialized) {
        auto result = start_color();
        assert(result == OK);
        initialized = true;
    }
}

void palette_base::init_pair(short pair, color f, color b)
{
    auto result = ::init_pair(
        pair,
        color_enum_to_ncurses(f),
        color_enum_to_ncurses(b)
    );

    assert(result == OK);
}

} // namespace detail
} // namespace ncursespp
