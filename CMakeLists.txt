cmake_minimum_required(VERSION 3.21.1)
project(learning-opengl
        VERSION 1.0
        DESCRIPTION "Learning OpenGL tutorial from https://learnopengl.com"
        HOMEPAGE_URL "https://github.com/cedmundo/learning-opengl"
        LANGUAGES C)
set(CMAKE_C_STANDARD 17)
include(ExternalProject)

# OpenGL and GLFW
find_package(OpenGL REQUIRED)
ExternalProject_Add(GLFW
    URL "https://github.com/glfw/glfw/archive/3.3.7.tar.gz"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/glfw_install"
)
set(GLFW_INCLUDE_DIR "${CMAKE_BINARY_DIR}/glfw_install/include/")
set(GLFW_LIBRARY_DIR "${CMAKE_BINARY_DIR}/glfw_install/lib/")

# Common utilities, such loading textures, shaders and so on ...
add_subdirectory(00-Utils)
set(UTILS_INCLUDE_DIR "../00-Utils/include")
function(configure_lecture TARGET)
    add_dependencies(${TARGET} GLFW)
    target_include_directories(${TARGET} PUBLIC ${UTILS_INCLUDE_DIR})
    target_include_directories(${TARGET} PUBLIC ${GLFW_INCLUDE_DIR})
    target_link_directories(${TARGET} PUBLIC ${GLFW_LIBRARY_DIR})
    target_link_libraries(${TARGET} LOUtils)
    target_link_libraries(${TARGET} glfw3)
endfunction()

# Actual lectures
add_subdirectory(01-HelloTriangle)