add_executable(
    reader
    main.cxx)

target_link_libraries(
    reader
    ncurses++

    # Works on FreeBSD's Clang 6
    c++experimental
)
