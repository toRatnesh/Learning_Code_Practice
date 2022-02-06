#
#       This example demonstates the use of cmake to build static, dynamic and exe binaries
#

cmake_minimum_required(VERSION 3.0.2)

message("=================================")
message("=== Processing ${CMAKE_CURRENT_LIST_FILE} ===")
message("=================================")

message("Using CMake version ${CMAKE_VERSION}")
message("")

message("       CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("       CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

message("       CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("       CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

message("       CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message("       CMAKE_CURRENT_LIST_FILE: ${CMAKE_CURRENT_LIST_FILE}")
message("       CMAKE_CURRENT_LIST_LINE: ${CMAKE_CURRENT_LIST_LINE}")
message("       CMAKE_PARENT_LIST_FILE: ${CMAKE_PARENT_LIST_FILE}")



#	END OF FILE
