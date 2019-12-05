include(FindCurses)

set(
    sources
    session.cxx
    color_rect.cxx
    palette.cxx
    text.cxx
)

add_library(
    ncurses++
    STATIC
    ${sources}
)

target_compile_features(
    ncurses++ PUBLIC cxx_std_17
)

target_include_directories (
    ncurses++
    PUBLIC
    ${NCPP_ROOT}/include
)

target_link_libraries(
    ncurses++
    PUBLIC
    ${CURSES_LIBRARIES}
)
