cmake_minimum_required(VERSION 3.31)
project(sudoku-solver C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")

add_executable(sudoku-solver main.c)

configure_file(sudoku.txt ${CMAKE_CURRENT_BINARY_DIR}/sudoku.txt COPYONLY)

