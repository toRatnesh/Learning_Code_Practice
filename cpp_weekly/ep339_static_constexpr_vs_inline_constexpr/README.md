
use 'static constexpr' for constexpr value at block scope
use 'inline constexpr' for constexpr value at file scope

This example demonstrate about 'static constexpr' and 'inline constexpr'

static constexpr:
    constexpr variable at block scope 
        sould be declared static to avoid copy of stack data
        can not be declared inline

inline constexpr:
    constexpr variable at file scope (or global scope)
    should be declared inline to avoid duplicacy of data 

    with inline at file scope
    $ g++ -std=c++17 main.cpp fun.cpp
    -rwxrwxr-x 1 ratnesh ratnesh 40013904 Sep  4 13:11 a.out

    with static at file scope
    $ g++ -std=c++17 main.cpp fun.cpp
    -rwxrwxr-x 1 ratnesh ratnesh 80015512 Sep  4 13:11 a.out


$ make
Compiling source file --- main.cpp
Compiling source file --- fun.cpp
Creating and linking executable --- ./constexpr

$ ll
total 195376
-rwxrwxr-x 1 ratnesh ratnesh 40013904 Sep  4 13:13 a.out
-rwxrwxr-x 1 ratnesh ratnesh 80015480 Sep  4 13:13 constexpr
-rw-rw-r-- 1 ratnesh ratnesh       65 Sep  3 19:55 fun.cpp
-rw-rw-r-- 1 ratnesh ratnesh      102 Sep  3 20:41 fun.hpp
-rw-rw-r-- 1 ratnesh ratnesh 40003280 Sep  4 13:13 fun.o
-rw-rw-r-- 1 ratnesh ratnesh       91 Sep  3 19:56 main.cpp
-rw-rw-r-- 1 ratnesh ratnesh 40003032 Sep  4 13:13 main.o
-rw-rw-r-- 1 ratnesh ratnesh      776 Sep  4 13:12 Makefile

