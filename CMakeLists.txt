cmake_minimum_required(VERSION 3.26)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(TicTacToe main.cpp)
