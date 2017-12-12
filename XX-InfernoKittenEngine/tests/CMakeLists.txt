include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

find_package(Check REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

# Copy assets and configure
file(COPY assets DESTINATION .)
set(CONTENT_PATH ${CMAKE_BINARY_DIR}/tests/assets)
configure_file(config.h.in config.h)

add_executable(vec2_test vec2_test.c)
target_link_libraries(vec2_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(vec2_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(vec3_test vec3_test.c)
target_link_libraries(vec3_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(vec3_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(vec4_test vec4_test.c)
target_link_libraries(vec4_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(vec4_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(mat4_test mat4_test.c)
target_link_libraries(mat4_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(mat4_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(mathutil_test mathutil_test.c)
target_link_libraries(mathutil_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(mathutil_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(quat_test quat_test.c)
target_link_libraries(quat_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(quat_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(pool_test pool_test.c)
target_link_libraries(pool_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(pool_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(hashmap_test hashmap_test.c)
target_link_libraries(hashmap_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(hashmap_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(spec_test spec_test.c)
target_link_libraries(spec_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(spec_test PUBLIC ${CMAKE_BINARY_DIR})

add_executable(asset_test asset_test.c)
target_link_libraries(asset_test ike ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(asset_test PUBLIC ${CMAKE_BINARY_DIR})
