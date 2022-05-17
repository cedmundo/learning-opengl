//
// Created by Carlos on 16/05/2022.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lofw/utils.h>

int main() {
    GLFWwindow *window = NULL;
    GLuint triangle_vbo = 0;
    GLuint triangle_vao = 0;
    GLuint triangle_vs = 0;
    GLuint triangle_fs = 0;
    GLuint triangle_sp = 0;
    char *triangle_vsd = NULL;
    char *triangle_fsd = NULL;
    int exit_code = 0;

    // Initialize the library
    if (!glfwInit()) {
        exit_code = -1;
        goto terminate;
    }

    // Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello triangle", NULL, NULL);
    if (!window) {
        exit_code = -1;
        goto terminate;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Load and compile shaders
    {
        triangle_vsd = load_text_file("./assets/hello_triangle.vs");
        CHECK_TEXT_FILE_ERROR(triangle_vsd, "./assets/hello_triangle.vs");

        triangle_vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(triangle_vs, 1, (const GLchar **) &triangle_vsd, NULL);
        glCompileShader(triangle_vs);
        CHECK_SHADER_COMPILE_ERROR(triangle_vs);

        triangle_fsd = load_text_file("./assets/hello_triangle.fs");
        CHECK_TEXT_FILE_ERROR(triangle_fsd, "./assets/hello_triangle.fs");

        triangle_fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(triangle_fs, 1, (const GLchar **) &triangle_fsd, NULL);
        glCompileShader(triangle_fs);
        CHECK_SHADER_COMPILE_ERROR(triangle_fs);

        triangle_sp = glCreateProgram();
        glAttachShader(triangle_sp, triangle_vs);
        glAttachShader(triangle_sp, triangle_fs);
        glLinkProgram(triangle_sp);
        CHECK_SHADER_LINK_ERROR(triangle_sp);
    }

    // Setup triangle object
    {
        // Vertex input
        float triangle_vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f,
        };

        // Generate VAO
        glGenVertexArrays(1, &triangle_vao);
        glBindVertexArray(triangle_vao);

        // Generate buffer and copy vertex data
        glGenBuffers(1, &triangle_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

        // Setup attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        {
            glUseProgram(triangle_sp);
            glBindVertexArray(triangle_vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    terminate:
    if (triangle_vs != 0) {
        glDeleteShader(triangle_vs);
    }

    if (triangle_fs != 0) {
        glDeleteShader(triangle_fs);
    }

    if (triangle_sp != 0) {
        glDeleteProgram(triangle_sp);
    }

    if (triangle_vsd != NULL) {
        unload_text_file(triangle_vsd);
    }

    if (triangle_fsd != NULL) {
        unload_text_file(triangle_fsd);
    }

    glDeleteBuffers(1, &triangle_vbo);
    if (window != NULL) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
    return exit_code;
}