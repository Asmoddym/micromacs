# Automatically generated CMakeLists.txt

cmake_minimum_required(VERSION 3.7.2)
project(micromacs)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
  set(CMAKE_C_FLAGS "-W -Wall -Wextra -g -ggdb3")
  set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")
endif(UNIX)

add_executable(micromacs ./src/io/file.c ./src/main.c ./src/modes/layout/layout.c ./src/modes/layout/navigate.c ./src/modes/layout/window.c ./src/modes/standard.c ./src/refresh.c ./src/run.c ./src/utils.c ./src/window.c)
target_include_directories(micromacs PRIVATE . ./src)
target_link_libraries(micromacs curses panel)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
