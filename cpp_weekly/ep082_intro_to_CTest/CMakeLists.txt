cmake_minimum_required(VERSION 3.0)

project(test_project)
set(CMAKE_CXX_STANDARD 14)
add_executable(ctest_prog ctest_prog.cpp ctest_prog_fun.cpp)


enable_testing()
add_executable(test_ctest_prog test_ctest_prog.cpp ctest_prog_fun.cpp)
add_test(tester_ctest_prog test_ctest_prog)
