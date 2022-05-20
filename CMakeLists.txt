cmake_minimum_required(VERSION 3.21.1)
project(learning-opengl
        VERSION 1.0
        DESCRIPTION "Learning OpenGL tutorial from https://learnopengl.com"
        HOMEPAGE_URL "https://github.com/cedmundo/learning-opengl"
        LANGUAGES C)
set(CMAKE_C_STANDARD 17)

include_directories(00-Utils/cmake)
include(ExternalProject)


# Dependencies
find_package(M)
find_package(X11)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

ExternalProject_Add(GLFW
    URL "https://github.com/glfw/glfw/archive/3.3.7.tar.gz"
    CMAKE_ARGS -DGLFW_BUILD_EXAMPLES=OFF
               -DGLFW_BUILD_TESTS=OFF
               -DGLFW_BUILD_DOCS=OFF
               -DGLFW_VULKAN_STATIC=OFF
               -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/glfw_install
    UPDATE_COMMAND ""
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
    target_link_libraries(${TARGET} ${OPENGL_LIBRARY})
    target_link_libraries(${TARGET} ${CMAKE_DL_LIBS})

    if(X11_FOUND)
        target_include_directories(${TARGET} PUBLIC ${X11_INCLUDE_DIR})
        target_link_libraries(${TARGET} ${X11_LIBRARIES})
    endif()

    target_link_libraries(${TARGET} Threads::Threads)
    if (HAVE_M)
        target_include_directories(${TARGET} PUBLIC ${M_INCLUDES})
        target_link_libraries(${TARGET} ${M_LIBRARIES})
    endif()

    set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    if (EXISTS ${ASSETS_DIR})
        add_custom_command(TARGET ${TARGET}
                PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/assets")
    endif()
endfunction()

# Actual lectures
add_subdirectory(01-HelloTriangle)
