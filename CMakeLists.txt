cmake_minimum_required(VERSION 3.3)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -std=c++11")

set(SOURCE_FILES main.cpp Snake.cpp Snake.h Board.cpp Board.h Game.cpp Game.h)
add_executable(Snake ${SOURCE_FILES})