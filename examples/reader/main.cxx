#include <ncurses++/vsplit.hpp>
#include <ncurses++/color_rect.hpp>
#include <ncurses++/session.hpp>
#include <ncurses++/palette.hpp>
#include <ncurses++/item_list.hpp>
#include <ncurses++/drawing.hpp>

#include <sstream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

struct file_display : public ncursespp::widget<file_display>
{
    void do_resize(ncursespp::rect_i r)
    {
        for (auto i = 0u; i < r.height() && i < content.size(); ++i) {
            auto rl = r;
            rl.left_top.y += i;
            rl.right_bottom.y = rl.left_top.y;

            ncursespp::draw::text(content[i], rl, 1);
        }
    }

    void load(fs::path &p)
    {
        std::ifstream is {p};
        std::string line;

        content.clear();

        while (std::getline(is, line)) {
            content.push_back(line);
        }

        do_resize(size());
    }

    std::vector<std::string> content;
};

struct list_item_file {
    static constexpr auto height = 1;

    list_item_file(list_item_file &&) = default;

    list_item_file(file_display &fd, const fs::path &p, const fs::file_status &fs)
        : path_ {p}
        , fs_ {fs}
        , fdisp_ {fd}
    {
    }

    void draw(int line, bool selected, ncursespp::rect_i r) const
    {
        auto color = line % 2 ? 1 : 2;
        color = selected ? 3 : color;
        ncursespp::draw::text(path_.filename().string(), r, color);
    }

    void activate()
    {
        fdisp_.load(path_);
    }

    fs::path path_;
    fs::file_status fs_;
    file_display &fdisp_;
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
void fill_list(fs::path p, List &list, file_display &fd)
{
    for (auto &e : fs::directory_iterator(p)) {
        list.append(list_item_file{fd, e.path(), e.status()});
    }
}

int main()
{
    using namespace ncursespp;
    namespace ct = constraint;
    session sess;

    auto pal = create_palette();
    auto list = item_list<list_item_file> {};
    auto fd = file_display {};

    auto vs = vsplit {
        ct::fixed<25>(list),
        ct::fixed<1>(color_rect{5}),
        ct::fill(fd)
    };

    fill_list(fs::current_path(), list, fd);

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
        } else if (c == 'd') {
            list.selected().activate();
        }
    }

    return 0;
}
