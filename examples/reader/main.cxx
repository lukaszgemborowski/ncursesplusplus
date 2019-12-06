#include <ncurses++/vsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/palette.hpp>
#include <ncurses++/item_list.hpp>
#include <ncurses++/drawing.hpp>

#include <sstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

struct list_item_file {
    static constexpr auto height = 1;

    list_item_file(list_item_file &&) = default;

    list_item_file(const fs::path &p, const fs::file_status &fs)
        : path_ {p}
        , fs_ {fs}
    {
    }

    void draw(int line, bool selected, ncursespp::rect_i r) const
    {
        auto color = line % 2 ? 1 : 2;
        color = selected ? 3 : color;
        ncursespp::draw::text(path_.filename().string(), r, color);
    }

    fs::path path_;
    fs::file_status fs_;
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


template<class List>
void fill(fs::path p, List &list)
{
    for (auto &e : fs::directory_iterator(p)) {
        list.append(list_item_file{e.path(), e.status()});
    }
}

int main()
{
    using namespace ncursespp;
    namespace ct = constraint;
    session sess;

    auto pal = create_palette();
    auto list = item_list<list_item_file> {};

    auto vs = vsplit {
        ct::fixed<25>(list),
        ct::fixed<1>(color_rect{5}),
        ct::fill(color_rect{1})
    };

    fill(fs::current_path(), list);

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
