cmake_minimum_required(VERSION 3.5.1)
project(LightingCasters)

# Modules (GLFW, GLAD, etc.)
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

# Finde dependencies
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)

# Local include
include_directories(include)

# Sources and headers
set(SOURCES src/glad.c src/main.c src/logl.c src/transform.c src/camera.c src/texture.c src/shader.c)
set(HEADERS include/glad/glad.h include/KHR/khrplatform.h include/logl.h include/camera.h include/texture.h include/shader.h)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS} ${PNG_LIBRARIES} m)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})

# Copy assets directory
file(INSTALL assets DESTINATION ${CMAKE_BINARY_DIR})
