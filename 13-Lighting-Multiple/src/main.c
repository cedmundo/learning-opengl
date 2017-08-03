#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>
#include <math.h>
#include <lmath/lmath.h>
#include <transform.h>
#include <camera.h>
#include <shader.h>
#include <texture.h>

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
                            "Lighting/Multiple", NULL, NULL);
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
        /* Positions */       /* Normals */        /* Texture Coords*/
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    loglShader phongShader;
    if (GL_FALSE == loglShaderLoad(&phongShader, "phong")) {
        excode = 1; goto finalize;
    }

    loglShader lampShader;
    if (GL_FALSE == loglShaderLoad(&lampShader, "lamp")) {
        excode = 1; goto finalize;
    }

    // Diffuse texture
    loglTexture diffuse;
    if (GL_FALSE == loglTextureLoad(&diffuse, "diffuse", "material.diffuse")) {
        excode = 1; goto finalize;
    }
    loglShaderAddTexture(phongShader, &diffuse);

    // Specular texture
    loglTexture specular;
    if (GL_FALSE == loglTextureLoad(&specular, "specular", "material.specular")) {
        excode = 1; goto finalize;
    }
    loglShaderAddTexture(phongShader, &specular);

    // Emission texture
    loglTexture emission;
    if (GL_FALSE == loglTextureLoad(&emission, "emission", "material.emission")) {
        excode = 1; goto finalize;
    }
    loglShaderAddTexture(phongShader, &emission);

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
        glEnableVertexAttribArray(0);

        // Set normals attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Set texture coords attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Use diffuse texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        loglTextureBind(&diffuse);
        loglTextureBind(&specular);
        loglTextureBind(&emission);
    glBindVertexArray(0);

    // Our lamp vertex array object, reuse vboCube
    GLuint vaoLamp;
    glGenVertexArrays(1, &vaoLamp);

    // Initialize figure
    glBindVertexArray(vaoLamp);
        glBindBuffer(GL_ARRAY_BUFFER, vboCube);

        // Set vertex positions attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
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

    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

    vec3 pointLightPositions[] = {
        { 0.7f,  0.2f,  2.0f},
        { 2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f, -12.0f},
        { 0.0f,  0.0f, -3.0f}
    };

    vec3 pointLightColors[] = {
        {0.1f, 0.0f, 0.1f},
        {0.0f, 0.1f, 0.0f},
        {0.1f, 0.0f, 0.1f},
        {0.0f, 0.1f, 0.0f}
    };

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

            // Change some stuff
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
                cubePositions[0] = vec3_add(cubePositions[0], vec3_scale(vec3_make(1.f, 0.f, 0.f), deltaTime * 2.f));
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                cubePositions[0] = vec3_add(cubePositions[0], vec3_scale(vec3_make(1.f, 0.f, 0.f), deltaTime * -2.f));
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
                cubePositions[0] = vec3_add(cubePositions[0], vec3_scale(vec3_make(0.f, 0.f, 1.f), deltaTime * -2.f));
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
                cubePositions[0] = vec3_add(cubePositions[0], vec3_scale(vec3_make(0.f, 0.f, 1.f), deltaTime * 2.f));

            // Get model for figure
            for (int i=0;i<10;i++) {
                float factor = lmath_radians(20.0f * i);
                figureTransform.rot = vec3_make(factor, factor * 0.3f, factor * 0.5f);
                figureTransform.pos = cubePositions[i];
                model = loglTransformGetModel(&figureTransform);

                float figureShininess = 32.f;
                float emitStrength = 0; // sin(currentFrame) + 0.4f;

                // Use the specified lightingShader
                loglShaderUse(phongShader);
                loglShaderSetMat4(phongShader, "model", model);
                loglShaderSetMat4(phongShader, "view", view);
                loglShaderSetMat4(phongShader, "projection", projection);
                loglShaderSetVec3(phongShader, "viewPos", camera.transform.pos);

                // DirectionalLight
                loglShaderSetVec3(phongShader, "dLight.direction", vec3_make(-0.2f, -1.0f, -0.3f));
                loglShaderSetVec3(phongShader, "dLight.ambient", vec3_make(0.1f, 0.1f, 0.1f));
                loglShaderSetVec3(phongShader, "dLight.diffuse", vec3_make(0.2f, 0.2f, 0.2f));
                loglShaderSetVec3(phongShader, "dLight.specular", vec3_make(1.0f, 1.0f, 1.0f));

                // PointLight
                for (int j=0;j<4;j++) {
                    loglShaderSetfVec3(phongShader, "pLights[%d].position", pointLightPositions[j], i);
                    loglShaderSetfVec3(phongShader, "pLights[%d].ambient", vec3_make(0.1f, 0.1f, 0.1f), i);
                    loglShaderSetfVec3(phongShader, "pLights[%d].diffuse", pointLightColors[j], i);
                    loglShaderSetfVec3(phongShader, "pLights[%d].specular", vec3_make(1.0f, 1.0f, 1.0f), i);
                    loglShaderSetfFloat(phongShader, "pLights[%d].constant", 1.0f, i);
                    loglShaderSetfFloat(phongShader, "pLights[%d].linear", 0.09f, i);
                    loglShaderSetfFloat(phongShader, "pLights[%d].quadratic", 0.052f, i);
                }

                // SpotLight
                loglShaderSetVec3(phongShader, "sLight.position", camera.transform.pos);
                loglShaderSetVec3(phongShader, "sLight.direction", camera.front);
                loglShaderSetVec3(phongShader, "sLight.ambient", vec3_make(0.1f, 0.1f, 0.1f));
                loglShaderSetVec3(phongShader, "sLight.diffuse", vec3_make(0.8f, 0.8f, 0.8f));
                loglShaderSetVec3(phongShader, "sLight.specular", vec3_make(1.0f, 1.0f, 1.0f));
                loglShaderSetFloat(phongShader, "sLight.cutOff", lmath_radians(60.f));
                loglShaderSetFloat(phongShader, "sLight.outerCutOff", lmath_radians(55.f));
                loglShaderSetFloat(phongShader, "sLight.constant", 1.0f);
                loglShaderSetFloat(phongShader, "sLight.linear", 0.09f);
                loglShaderSetFloat(phongShader, "sLight.quadratic", 0.032f);

                // Set material uniforms
                loglShaderSetFloat(phongShader, "material.shininess", figureShininess);
                loglShaderSetFloat(phongShader, "material.emitStrength", emitStrength);
                loglShaderSetTextures(phongShader);

                // Draw the object
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
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
    glfwTerminate();
    return excode;
}
