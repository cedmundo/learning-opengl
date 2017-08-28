include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

add_executable(check_vec2 check_vec2.c)
target_link_libraries(check_vec2 ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(check_vec3 check_vec3.c)
target_link_libraries(check_vec3 ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(check_vec4 check_vec4.c)
target_link_libraries(check_vec4 ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
