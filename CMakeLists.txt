cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
project(streamline-ux)

include_directories(${CMAKE_SOURCE_DIR}/include)

file (GLOB SOURCES
    "src/*.cpp"
    "src/ux/*.cpp"
)

find_package(Curses REQUIRED)

add_executable(streamline-ux ${SOURCES})
target_compile_options(streamline-ux PRIVATE -Werror -Wall -Wpedantic -D_XOPEN_SOURCE_EXTENDED -g )

include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(streamline-ux ${CURSES_LIBRARIES})