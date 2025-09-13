cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)

project(Belot)

add_executable(exe Player.cpp Round.cpp BiddingState.cpp PlayingState.cpp Game.cpp main.cpp)
