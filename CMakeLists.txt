cmake_minimum_required(VERSION 3.23)
project(fc3)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(fc3 main.cpp GameSystem.cpp Level.h Level.cpp Player.cpp Enemy.h Enemy.cpp MazeGen.cpp)

target_link_libraries(fc3 ${CURSES_LIBRARIES})
#target_link_libraries(fc3 ncurses)
#target_link_libraries(fefclion3 ${CURSES_LIBRARY})
