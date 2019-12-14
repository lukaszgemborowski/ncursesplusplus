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

set(
    inc-dir
    ${NCPP_ROOT}/include/ncurses++/
)

set(
    headers
    ${inc-dir}/attributes.hpp
    ${inc-dir}/color.hpp
    ${inc-dir}/color_rect.hpp
    ${inc-dir}/constraints.hpp
    ${inc-dir}/drawing.hpp
    ${inc-dir}/hsplit.hpp
    ${inc-dir}/item_list.hpp
    ${inc-dir}/palette.hpp
    ${inc-dir}/rect.hpp
    ${inc-dir}/session.hpp
    ${inc-dir}/text.hpp
    ${inc-dir}/text_list.hpp
    ${inc-dir}/vsplit.hpp
    ${inc-dir}/widget.hpp
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

install(
    TARGETS ncurses++
    ARCHIVE DESTINATION lib
)

install(
    FILES ${headers}
    DESTINATION include/ncurses++
)
