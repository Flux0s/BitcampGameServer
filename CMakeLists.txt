cmake_minimum_required(VERSION 3.7)
project(Bitcamp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Client.h Client.cpp Game.cpp Game.h)
add_executable(Bitcamp ${SOURCE_FILES})