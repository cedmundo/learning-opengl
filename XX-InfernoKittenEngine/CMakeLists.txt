project(ike C)

# Misc configuration
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BUILD_TYPE Debug)

# Project settings
set(IKE_MAJOR_VERSION 0)
set(IKE_MINOR_VERSION 1)
set(IKE_PATCH_VERSION 0)
set(IKE_VERSION
    ${FOOBAR_MAJOR_VERSION}.${FOOBAR_MINOR_VERSION}.${FOOBAR_PATCH_VERSION})

# Some lib check conditions
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

# Check headers
set(INCLUDES "")
macro(ck_check_include_file header var)
  check_include_files("${INCLUDES};${header}" ${var})
  if(${var})
    set(INCLUDES ${INCLUDES} ${header})
  endif(${var})
endmacro(ck_check_include_file)

ck_check_include_file("stdlib.h" HAVE_STDLIB_H)

# Check functions
# (Nothing to check)

# Check defines
# (Nothing to check)

# Check struct members
# (Nothing to check)

# Check for integer types
check_type_size(intmax_t INTMAX_T)
check_type_size(uintmax_t UINTMAX_T)

check_type_size(pid_t PID_T)
if(NOT HAVE_PID_T)
  if(WIN32)
    set(pid_t "int")
  else(WIN32)
    MESSAGE(FATAL_ERROR "pid_t doesn't exist on this platform?")
  endif(WIN32)
endif(NOT HAVE_PID_T)

# Generate "config.h" from "cmake/config.h.cmake"
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG_H)
set(CONFIG_HEADER ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# We need to add include directory
include_directories(include)

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Unit tests
enable_testing()
add_test(NAME mathutil_test COMMAND mathutil_test)
add_test(NAME vec2_test COMMAND vec2_test)
add_test(NAME vec3_test COMMAND vec3_test)
add_test(NAME vec4_test COMMAND vec4_test)
add_test(NAME mat4_test COMMAND mat4_test)

