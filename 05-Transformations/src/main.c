#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>
#include <math.h>
#include <lmath/lmath.h>
#include <transform.h>

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
                            "Transformations", NULL, NULL);
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
        /* Positions */       /* Colors */          /* Texture coords */
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
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

    // Load texture image data
    GLchar *texdata0 = NULL;
    GLuint texw0, texh0;
    if (GL_FALSE == loglLoadPNG("assets/texture0.png", &texdata0, &texw0, &texh0)) {
        excode = 1; goto finalize;
    }

    GLchar *texdata1 = NULL;
    GLuint texw1, texh1;
    if (GL_FALSE == loglLoadPNG("assets/texture1.png", &texdata1, &texw1, &texh1)) {
        excode = 1; goto finalize;
    }

    loglTransform transform;
    transform.pos = vec3_make(0.0f, 0.0f, 0.0f);
    transform.rot = vec3_make(0.0f, 0.0f, 0.0f);
    transform.sca = vec3_make(1.0f, 1.0f, 1.0f);

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
        glEnableVertexAttribArray(0);
        // Set vertex color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Set vertex texture coords attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        // Create textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLuint texture0;
        glGenTextures(1, &texture0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texw0, texh0, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata0);
        glGenerateMipmap(GL_TEXTURE_2D);

        GLuint texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texw1, texh1, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata1);
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindVertexArray(0);

    // Render loop
    while(GL_FALSE == glfwWindowShouldClose(window)) {
        // Input processing
        loglProcessInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw figure
        glBindVertexArray(vboFigure);
            // Use the specified shaderProgram
            glUseProgram(shaderProgram);

            // Update the transform
            float time = (float) glfwGetTime();
            transform.rot.x = time;
            transform.rot.y = time;
            transform.rot.z = time;
            transform.pos.x = sinf(time) * 0.5;
            transform.pos.y = cosf(time) * 0.5;
            //transform.sca.x = cosf(time) * 0.2 + 1.0;
            //transform.sca.y = cosf(time) * 0.2 + 1.0;
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, logl_transform_get_model(&transform).raw);

            // Use loaded texture0
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);

            // Use loaded texture1
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glUniform1i(glGetUniformLocation(shaderProgram, "tex1"), 1);

            // Draw the object
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // Forget texture
            glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            printf("[ERROR] OpenGL errCode=%d\n", err);
        }

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

    if (texdata0 != 0)
        loglUnloadPNG(texdata0);

    if (texdata1 != 0)
        loglUnloadPNG(texdata1);

    glfwTerminate();
    return excode;
}
