cmake_minimum_required(VERSION 3.16.3)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_CXX_STANDARD 20)

project(Belot)

add_executable(exe Player.cpp Round.cpp BiddingState.cpp PlayingState.cpp Game.cpp main.cpp)
