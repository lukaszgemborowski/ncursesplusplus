#ifndef NCURSESPP_SESSION_HPP
#define NCURSESPP_SESSION_HPP

#include <ncurses++/rect.hpp>

namespace ncursespp
{

class session
{
public:
    session();
    ~session();

    session(session &&) = default;

    session(const session &) = delete;
    session& operator=(const session &) = delete;
    session& operator=(session &&) = delete;

    void refresh();
    rect_i size() const;
    int getkey() const;
};

} // namespace ncursespp

#endif // NCURSESPP_SESSION_HPP
