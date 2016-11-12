cmake_minimum_required(VERSION 3.5)
project(ProjetoTG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Principal.cpp Principal.h Util.cpp PreProcessing.cpp Processing.cpp Util.h PreProcessing.h main.cpp ExactAlgorithm.cpp ExactAlgorithm.h)
add_executable(ProjetoTG ${SOURCE_FILES})