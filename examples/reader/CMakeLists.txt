add_executable(
    reader
    main.cxx)

target_link_libraries(
    reader
    ncurses++

    # clang 6.0.1 @ FreeBSD, needs to be fixed for GCC and other platforms
    c++experimental
)
