#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>
#include <math.h>
#include <lmath/lmath.h>
#include <transform.h>
#include <camera.h>

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
                            "Lighting/Colors", NULL, NULL);
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
        /* Positions */
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    // Compile vertex shader
    GLchar* vSource;
    if (GL_FALSE == loglLoadText("assets/lighting.vert", &vSource)) {
        excode = 1; vSource = 0; goto finalize;
    }

    GLuint vShader;
    if (GL_FALSE == loglCompileShaderStr(&vShader, GL_VERTEX_SHADER, vSource)) {
        excode = 1; vShader = 0; goto finalize;
    }

    // Compile fragment shader
    GLchar* fSource;
    if (GL_FALSE == loglLoadText("assets/lighting.frag", &fSource)) {
        excode = 1; fSource = 0; goto finalize;
    }

    GLuint fShader;
    if (GL_FALSE == loglCompileShaderStr(&fShader, GL_FRAGMENT_SHADER, fSource)) {
        excode = 1; fShader = 0; goto finalize;
    }

    // Create shader program
    GLuint lightingShader;
    if (GL_FALSE == loglGetShaderProgram(&lightingShader, vShader, fShader)) {
        excode = 1; goto finalize;
    }

    // Clean shaders for re-use
    if (vShader != 0)
        glDeleteShader(vShader);

    if (fShader != 0)
        glDeleteShader(fShader);

    if (vSource != 0)
        loglUnloadText(vSource);

    if (fSource != 0)
        loglUnloadText(fSource);


    if (GL_FALSE == loglLoadText("assets/lamp.vert", &vSource)) {
        excode = 1; vSource = 0; goto finalize;
    }

    if (GL_FALSE == loglCompileShaderStr(&vShader, GL_VERTEX_SHADER, vSource)) {
        excode = 1; vShader = 0; goto finalize;
    }

    if (GL_FALSE == loglLoadText("assets/lamp.frag", &fSource)) {
        excode = 1; fSource = 0; goto finalize;
    }

    if (GL_FALSE == loglCompileShaderStr(&fShader, GL_FRAGMENT_SHADER, fSource)) {
        excode = 1; fShader = 0; goto finalize;
    }

    GLuint lampShader;
    if (GL_FALSE == loglGetShaderProgram(&lampShader, vShader, fShader)) {
        excode = 1; goto finalize;
    }

    // Our cube vertex buffer object
    GLuint vboCube;
    glGenBuffers(1, &vboCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Our figure vertex array object, reuse vboCube
    GLuint vaoFigure;
    glGenVertexArrays(1, &vaoFigure);
    // Initialize figure
    glBindVertexArray(vaoFigure);
        glBindBuffer(GL_ARRAY_BUFFER, vboCube);

        // Set vertex positions attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Our lamp vertex array object, reuse vboCube
    GLuint vaoLamp;
    glGenVertexArrays(1, &vaoLamp);

    // Initialize figure
    glBindVertexArray(vaoLamp);
        glBindBuffer(GL_ARRAY_BUFFER, vboCube);

        // Set vertex positions attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Figure transform
    loglTransform figureTransform;
    figureTransform.pos = vec3_make(0.0f, 0.0f, 0.0f);
    figureTransform.rot = vec3_make(0.0f, 0.0f, 0.0f);
    figureTransform.sca = vec3_make(1.0f, 1.0f, 1.0f);

    // Lamp transform
    loglTransform lampTransform;
    lampTransform.pos = vec3_make(6.0f, 0.0f, 6.0f);
    lampTransform.rot = vec3_make(0.0f, 0.0f, 0.0f);
    lampTransform.sca = vec3_make(0.2f, 0.2f, 0.2f);

    loglCamera camera;
    loglCameraInit(&camera, window);
    camera.transform.pos = vec3_make(-4.0f, 0.0f, 0.0f);
    camera.transform.rot = vec3_make(lmath_radians(90.0f), 0.0f, 0.0f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;

    // Render loop
    while(GL_FALSE == glfwWindowShouldClose(window)) {
        // Time stuff
        currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input processing
        loglProcessInput(window);

        // Update camera stuff
        loglCameraUpdate(&camera, deltaTime);

        // Rendering commands
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // Draw figure
        glBindVertexArray(vboCube);
            mat4 model, view, projection;

            // Get camera view and projection matrices
            view = loglCameraGetView(&camera);
            projection = loglCameraGetProjection(&camera);


            // Get model for figure
            model = loglTransformGetModel(&figureTransform);

            // Use the specified lightingShader
            glUseProgram(lightingShader);
            glUniformMatrix4fv(glGetUniformLocation(lightingShader, "model"), 1, GL_FALSE, model.raw);
            glUniformMatrix4fv(glGetUniformLocation(lightingShader, "view"), 1, GL_FALSE, view.raw);
            glUniformMatrix4fv(glGetUniformLocation(lightingShader, "projection"), 1, GL_FALSE, projection.raw);

            glUniform3fv(glGetUniformLocation(lightingShader, "objectColor"), 1, vec3_make(1.0f, 0.5f, 0.31f).xyz);
            glUniform3fv(glGetUniformLocation(lightingShader, "lightColor"), 1, vec3_make(1.0f, 1.0f, 1.0f).xyz);

            // Draw the object
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Get model for lamp
            model = loglTransformGetModel(&lampTransform);

            // Use the specified lightingShader
            glUseProgram(lampShader);
            glUniformMatrix4fv(glGetUniformLocation(lampShader, "model"), 1, GL_FALSE, model.raw);
            glUniformMatrix4fv(glGetUniformLocation(lampShader, "view"), 1, GL_FALSE, view.raw);
            glUniformMatrix4fv(glGetUniformLocation(lampShader, "projection"), 1, GL_FALSE, projection.raw);

            // Draw the object
            glDrawArrays(GL_TRIANGLES, 0, 36);
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

    glfwTerminate();
    return excode;
}
