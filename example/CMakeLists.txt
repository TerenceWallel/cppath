cmake_minimum_required(VERSION 3.01)

project(cppath_example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include_directories(../include)
add_executable(cppath_example example.cpp ../include/cppath_base.hpp ../include/cppath_config.h ../include/cppath_vector.hpp)

