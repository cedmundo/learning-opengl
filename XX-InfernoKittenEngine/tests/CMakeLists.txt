include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

add_executable(vec2_test vec2_test.c)
target_link_libraries(vec2_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(vec3_test vec3_test.c)
target_link_libraries(vec3_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(vec4_test vec4_test.c)
target_link_libraries(vec4_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(mat4_test mat4_test.c)
target_link_libraries(mat4_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(mathutil_test mathutil_test.c)
target_link_libraries(mathutil_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(quat_test quat_test.c)
target_link_libraries(quat_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
