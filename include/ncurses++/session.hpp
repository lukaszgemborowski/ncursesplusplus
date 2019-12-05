#ifndef NCURSESPP_SESSION_HPP
#define NCURSESPP_SESSION_HPP

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
};

} // namespace ncursespp

#endif // NCURSESPP_SESSION_HPP
