# Automatically generated CMakeLists.txt

cmake_minimum_required(VERSION 3.7.2)
project(c)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
  set(CMAKE_C_FLAGS "-W -Wall -Wextra -g -ggdb3")
  set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")
endif(UNIX)

include_directories(. )

add_executable(c ./src/main.c)
target_link_libraries(c curses)
