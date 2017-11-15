include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
find_package(Msgpack REQUIRED)

include_directories(${MSGPACK_INCLUDE_DIRS})
add_executable(ike-config-display ike-config-display.c)
target_link_libraries(ike-config-display ike ${MSGPACK_LIBRARIES})
