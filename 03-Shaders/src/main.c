#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>
#include <math.h>

int main() {
    GLint excode = 0;

    // Init glfw
    if(GL_FALSE == glfwInit()) {
        printf("[ERROR] Could not initialize GLFW.\n");
        excode = 1; goto finalize;
    }

    // Init GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(
                            LOGL_WINDOW_WIDTH,
                            LOGL_WINDOW_HEIGHT,
                            "Shaders", NULL, NULL);
    if (window == NULL) {
        printf("[ERROR] Could not create window\n");
        excode = 1; goto finalize;
    }

    // Handle default window on this thread
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, loglResizeCb);

    // Load GLAD
    if (GL_FALSE == gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("[ERROR] Failed to initialize GLAD\n");
        excode = 1; goto finalize;
    }

    glViewport(0, 0, LOGL_WINDOW_WIDTH, LOGL_WINDOW_HEIGHT);

    // Pre-processing
    GLfloat vertices[] = {
         /* Positions */        /* Colors */
         -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
          0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
          0.0f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
    };

    // Compile vertex shader
    GLchar* vSource;
    if (GL_FALSE == loglLoadText("assets/default.vert", &vSource)) {
        excode = 1; vSource = 0; goto finalize;
    }

    GLuint vShader;
    if (GL_FALSE == loglCompileShaderStr(&vShader, GL_VERTEX_SHADER, vSource)) {
        excode = 1; vShader = 0; goto finalize;
    }

    // Compile fragment shader
    GLchar* fSource;
    if (GL_FALSE == loglLoadText("assets/default.frag", &fSource)) {
        excode = 1; fSource = 0; goto finalize;
    }

    GLuint fShader;
    if (GL_FALSE == loglCompileShaderStr(&fShader, GL_FRAGMENT_SHADER, fSource)) {
        excode = 1; fShader = 0; goto finalize;
    }

    // Create shader program
    GLuint shaderProgram;
    if (GL_FALSE == loglGetShaderProgram(&shaderProgram, vShader, fShader)) {
        excode = 1; goto finalize;
    }

    // Color intensity uniform
    GLuint colsatLoc = glGetUniformLocation(shaderProgram, "colsat");

    // Our figure vertex buffer object
    GLuint vboFigure;
    glGenBuffers(1, &vboFigure);
    // Our figure element buffer object
    GLuint eboFigure;
    glGenBuffers(1, &eboFigure);
    // Our figure vertex array object
    GLuint vaoFigure;
    glGenVertexArrays(1, &vaoFigure);

    // Initialize figure
    glBindVertexArray(vaoFigure);
        // Copy vertex data to buffer
        glBindBuffer(GL_ARRAY_BUFFER, vboFigure);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // Copy index data to buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboFigure);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // Set vertex positions attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
        glEnableVertexAttribArray(0);
        // Set vertex color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Render loop
    while(GL_FALSE == glfwWindowShouldClose(window)) {
        // Input processing
        loglProcessInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLfloat etime = glfwGetTime();
        GLfloat colsat = sin(etime) / 1.0f + 1.0f;

        // Draw figure
        glBindVertexArray(vboFigure);
            // Use the specified shaderProgram
            glUseProgram(shaderProgram);
            // Set uniform value
            glUniform1f(colsatLoc, colsat);
            // Draw the object
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers and check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

finalize:
    if (vShader != 0)
        glDeleteShader(vShader);

    if (fShader != 0)
        glDeleteShader(fShader);

    if (vSource != 0)
        loglUnloadText(vSource);

    if (fSource != 0)
        loglUnloadText(fSource);

    glfwTerminate();
    return excode;
}
