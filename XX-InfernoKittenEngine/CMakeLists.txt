# Project setup
cmake_minimum_required(VERSION 2.8)
project(ike C)

# Extra modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BUILD_TYPE Debug)

# Add sources
add_subdirectory(src)
add_subdirectory(tests)
#add_subdirectory(tools)

enable_testing()
include(Testing)
