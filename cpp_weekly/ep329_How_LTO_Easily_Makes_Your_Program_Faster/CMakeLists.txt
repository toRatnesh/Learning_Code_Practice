project(mytest CXX)

cmake_minimum_required(VERSION 3.5)

add_executable(mytest
    main.cpp
    static.cpp
    dynamic.cpp)

target_link_libraries(mytest
    fmtd)
