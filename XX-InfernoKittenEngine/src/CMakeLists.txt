# This library
set(IKE_LIBNAME ike)

# Create library
set(IKE_SOURCES
  ike.c
  hashmap.c
  pool.c
  asset.c
  )

# Find packages
find_package(Msgpack REQUIRED)
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

# Generate the static library from the sources
add_library(${IKE_LIBNAME} STATIC ${IKE_SOURCES})
target_link_libraries(ike ${MSGPACK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
target_include_directories(${IKE_LIBNAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
