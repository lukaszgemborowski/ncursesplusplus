cmake_minimum_required (VERSION 3.2)
project (ncurses++)

set(NCPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option(NCURSESPP_BUILD_EXAMPLES "build all examples" ON)

add_subdirectory(src)

if (NCURSESPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
