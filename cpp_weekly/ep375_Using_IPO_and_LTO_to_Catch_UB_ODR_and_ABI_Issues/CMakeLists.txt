
cmake_minimum_required(VERSION 3.5)

project(the_exe CXX)
add_executable(the_exe use.cpp get.cpp main.cpp)
set_property(TARGET the_exe PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)


