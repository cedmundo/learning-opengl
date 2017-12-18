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

# External projects

# START Msgpack External Dependency
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
set(MSGPACK_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgpack-c-install)
ExternalProject_Add(msgpack-c
    GIT_REPOSITORY "https://github.com/msgpack/msgpack-c.git"
    GIT_TAG cpp-2.1.5
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/vendor/msgpack-c
    INSTALL_DIR ${MSGPACK_INSTALL_DIR}
    BINARY_DIR ${MSGPACK_INSTALL_DIR}
    CMAKE_ARGS -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
               -DCMAKE_INSTALL_PREFIX=${MSGPACK_INSTALL_DIR}
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    BUILD_COMMAND make
    )
# END msgpack

# Find packages
# find_package(Msgpack REQUIRED)
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)

# Generate the static library from the sources
add_library(${IKE_LIBNAME} STATIC ${IKE_SOURCES})
target_include_directories(${IKE_LIBNAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})
target_link_libraries(${IKE_LIBNAME} PUBLIC  ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${PNG_LIBRARIES} ${CMAKE_DL_LIBS} m)

target_include_directories(${IKE_LIBNAME} PUBLIC ${MSGPACK_INSTALL_DIR}/include)
target_link_libraries(${IKE_LIBNAME} PUBLIC ${MSGPACK_INSTALL_DIR}/lib/libmsgpackc.a ${MSGPACK_INSTALL_DIR}/lib/libmsgpackc.so)
