# This library
set(IKE_LIBNAME ike)

# Create library
set(IKE_SOURCES
    glad.c
    ike.c
    pool.c
    hashmap.c
    spec.c
    spec_decode.c
    image.c
    image_decode.c
    asset.c
    timer.c
    presenter.c
  )

# Find packages
find_package(Msgpack REQUIRED)
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)

# Generate the static library from the sources
add_library(${IKE_LIBNAME} STATIC ${IKE_SOURCES})
target_link_libraries(ike ${MSGPACK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${PNG_LIBRARIES} ${CMAKE_DL_LIBS} m)
target_include_directories(${IKE_LIBNAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})
