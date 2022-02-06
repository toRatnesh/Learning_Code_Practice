#
#	This example demonstates the use of cmake to build static, dynamic and exe binaries
#


cmake_minimum_required(VERSION 3.0.2)

message("=================================")
message("=== Processing ${CMAKE_CURRENT_LIST_FILE} ===")
message("=================================")

message("Using CMake version ${CMAKE_VERSION}")
message("")

message("Before project():")
message("	C Compiler: ${CMAKE_C_COMPILER}")
message("	C++ Compiler: ${CMAKE_CXX_COMPILER}")
message("	Source: ${PROJECT_SOURCE_DIR}")
message("	Binary: ${PROJECT_BINARY_DIR}")
message("	Version: ${PROJECT_VERSION}")
message("	Version (alt): ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
message("")

project(cmake_learning VERSION 1.2.3.4)

message("After project():")
message("	C Compiler: ${CMAKE_C_COMPILER}")
message("	C++ Compiler: ${CMAKE_CXX_COMPILER}")
message("	Source: ${PROJECT_SOURCE_DIR}")
message("	Binary: ${PROJECT_BINARY_DIR}")
message("	Version: ${PROJECT_VERSION}")
message("	Version (alt): ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")

message("")
include(ProcessorCount)
ProcessorCount(N)
message("Number of processors: ${N}")

message("")
message("=== Adding Subdirectory ===")
message("	CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("	CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

message("       CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("       CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

message("       CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message("       CMAKE_CURRENT_LIST_FILE: ${CMAKE_CURRENT_LIST_FILE}")
message("       CMAKE_CURRENT_LIST_LINE: ${CMAKE_CURRENT_LIST_LINE}")
message("       CMAKE_PARENT_LIST_FILE: ${CMAKE_PARENT_LIST_FILE}")

add_subdirectory(src)


#	END OF FILE
