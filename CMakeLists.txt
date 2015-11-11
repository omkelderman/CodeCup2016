cmake_minimum_required(VERSION 3.3)
project(CodeCup)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

set(SOURCE_FILES main.cpp Game6561.cpp Game6561.h Board.cpp Board.h Piece.cpp Piece.h Algorithm.cpp Algorithm.h MonteCarloAlgorithm.cpp MonteCarloAlgorithm.h TestAlgorithm.cpp TestAlgorithm.h GameException.cpp GameException.h)
add_executable(CodeCup ${SOURCE_FILES})