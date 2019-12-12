include(FindCurses)

set(
    sources
    session.cxx
    color_rect.cxx
    palette.cxx
    text.cxx
    text_list.cxx
    drawing.cxx
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

target_compile_options(
    ncurses++
    PRIVATE
    -Wall
    -Werror
)
