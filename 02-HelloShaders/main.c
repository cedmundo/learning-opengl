//
// Created by Carlos on 16/05/2022.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lofw/utils.h>
// #include <math.h>

#define USE_GL_MODE GL_FILL // GL_LINE | GL_FILL

int main() {
    GLFWwindow *window = NULL;
    GLuint figure_vbo = 0;
    GLuint figure_vao = 0;
    GLuint figure_ebo = 0;
    GLuint figure_vs = 0;
    GLuint figure_fs = 0;
    GLuint figure_sp = 0;
    GLchar *figure_vsd = NULL;
    GLchar *figure_fsd = NULL;
    GLint exit_code = 0;

    // Initialize the library
    CHECK_ERROR(!glfwInit());
    glfwSetErrorCallback(report_glfw_error_cb);

    // Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello shaders", NULL, NULL);
    CHECK_ERROR(!window);

    // Make the window's context current
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Load and compile shaders
    {
        figure_vsd = load_text_file("./assets/hello_shaders.vs");
        CHECK_TEXT_FILE_ERROR(figure_vsd, "./assets/hello_shaders.vs");

        figure_vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(figure_vs, 1, (const GLchar **) &figure_vsd, NULL);
        glCompileShader(figure_vs);
        CHECK_SHADER_COMPILE_ERROR(figure_vs);

        figure_fsd = load_text_file("./assets/hello_shaders.fs");
        CHECK_TEXT_FILE_ERROR(figure_fsd, "./assets/hello_shaders.fs");

        figure_fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(figure_fs, 1, (const GLchar **) &figure_fsd, NULL);
        glCompileShader(figure_fs);
        CHECK_SHADER_COMPILE_ERROR(figure_fs);

        figure_sp = glCreateProgram();
        glAttachShader(figure_sp, figure_vs);
        glAttachShader(figure_sp, figure_fs);
        glLinkProgram(figure_sp);
        CHECK_SHADER_LINK_ERROR(figure_sp);
    }

    // Setup triangle object
    {
        // Vertex input
        GLfloat figure_vertices[] = {
                // positions                    // colors
                -0.5f,-0.5f,0.0f,   1.0f, 0.0f, 0.0f,
                 0.5f,-0.5f,0.0f,   0.0f, 1.0f, 0.0f,
                0.0f, 0.5f,0.0f, 0.0f, 0.0f, 1.0f,
        };

        // Drawing indices
        GLuint indices[] = {
                0, 1, 2,
        };

        glGenBuffers(1, &figure_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, figure_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Generate VAO
        glGenVertexArrays(1, &figure_vao);
        glBindVertexArray(figure_vao);

        // Generate buffer and copy vertex data
        glGenBuffers(1, &figure_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, figure_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(figure_vertices), figure_vertices, GL_STATIC_DRAW);

        // Setup attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        {
            // GLdouble time_value = glfwGetTime();
            // GLdouble green_value = (sin(time_value) / 2.0f) + 0.5f;
            // GLint figure_our_color_uniform_loc = glGetUniformLocation(figure_sp, "ourColor");

            glPolygonMode(GL_FRONT_AND_BACK, USE_GL_MODE);
            glUseProgram(figure_sp);
            // glUniform4f(figure_our_color_uniform_loc, 0.0f, (GLfloat)green_value, 0.0f, 1.0f);
            glBindVertexArray(figure_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, figure_ebo);
            glDrawElements(GL_TRIANGLES, sizeof(figure_ebo), GL_UNSIGNED_INT, 0);
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    terminate:
    if (figure_vs != 0) {
        glDeleteShader(figure_vs);
    }

    if (figure_fs != 0) {
        glDeleteShader(figure_fs);
    }

    if (figure_sp != 0) {
        glDeleteProgram(figure_sp);
    }

    if (figure_vsd != NULL) {
        unload_text_file(figure_vsd);
    }

    if (figure_fsd != NULL) {
        unload_text_file(figure_fsd);
    }

    if (figure_vao != 0) {
        glDeleteVertexArrays(1, &figure_vao);
    }

    if (figure_ebo != 0) {
        glDeleteBuffers(1, &figure_ebo);
    }

    if (figure_vbo != 0) {
        glDeleteBuffers(1, &figure_vbo);
    }

    if (window != NULL) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
    return exit_code;
}