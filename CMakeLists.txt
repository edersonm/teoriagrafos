cmake_minimum_required(VERSION 3.5)
project(ProjetoTG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Util.h Util.cpp Exato.h Exato.cpp GA.h GA.cpp main.cpp)
add_executable(ProjetoTG ${SOURCE_FILES})