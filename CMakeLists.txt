cmake_minimum_required(VERSION 3.3)
project(CodeCup)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CodeCup ${SOURCE_FILES})