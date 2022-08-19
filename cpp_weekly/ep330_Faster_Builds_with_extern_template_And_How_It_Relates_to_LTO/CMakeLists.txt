project(mytest CXX)

cmake_minimum_required(VERSION 3.5)

add_executable(mytest
    main.cpp
    addition.cpp)

target_link_libraries(mytest
    fmtd)

set_property(TARGET mytest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
