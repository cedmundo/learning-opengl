
# Find packages
find_package(Msgpack REQUIRED)
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

set(LIB_SOURCES
    ike.c
    asset.c
    display.c
    )

set(HEADERS
    ${CONFIG_HEADER}
    ../include/glad/glad.h
    ../include/KHR/khrplatform.h
    ../include/ike/asset.h
    ../include/ike/display.h
    )

include_directories(src)
add_library(ike STATIC ${LIB_SOURCES} ${HEADERS})
target_link_libraries(ike ${MSGPACK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
target_include_directories(ike PUBLIC ${MSGPACK_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

install(TARGETS ike
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ike.h DESTINATION include)

