#include <ncurses++/drawing.hpp>
#include <ncurses.h>

namespace
{

auto attributes_enum_to_ncurses(ncursespp::attribute attr)
{
    using namespace ncursespp;

    switch (attr)
    {
    case attribute::normal: return A_NORMAL;
    case attribute::standout: return A_STANDOUT;
    case attribute::underline: return A_UNDERLINE;
    case attribute::reverse: return A_REVERSE;
    case attribute::blink: return A_BLINK;
    case attribute::dim: return A_DIM;
    case attribute::bold: return A_BOLD;
    case attribute::italic: return A_ITALIC;
    }

    return A_NORMAL;
}

} // namespace

namespace ncursespp
{

void draw::fill_rect(rect_i r, short color)
{
    auto lt = r.left_top;
    auto rb = r.right_bottom;

    attron(COLOR_PAIR(color));

    for (int x = lt.x; x <= rb.x; ++x) {
        for (int y = lt.y; y <= rb.y; ++y) {
            mvaddch(y, x, ' ');
        }
    }

    attroff(COLOR_PAIR(color));
}

int draw::text(const std::string &text, rect_i r, short color)
{
    auto lt = r.left_top;
    int res = 0;
    fill_rect(r, color); // TODO: optimize!

    attron(COLOR_PAIR(color));
    for (auto i = 0u;
         static_cast<int>(i) < r.width() && i < text.size();
         ++i) {
        mvaddch(lt.y, lt.x + i, text[i]);
        res ++;
    }
    attroff(COLOR_PAIR(color));
    return res;
}

void draw::attribute_on(attribute attr)
{
    attron(attributes_enum_to_ncurses(attr));
}

void draw::attribute_off(attribute attr)
{
    attroff(attributes_enum_to_ncurses(attr));
}

} // namespace ncursespp
