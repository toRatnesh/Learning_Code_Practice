cmake_minimum_required(VERSION 3.5)

project(static_order)

set(CMAKE_CXX_STANDARD 20)

add_executable(the_executable
    provider.cpp
    consumer.cpp
    main.cpp)


