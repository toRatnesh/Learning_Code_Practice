project(cpp17_inline CXX)

cmake_minimum_required(VERSION 3.5)

add_executable(cpp17_inline
    main.cpp
    fun1.cpp
    fun2.cpp
    common.cpp)

target_compile_features(cpp17_inline PRIVATE cxx_std_14)


