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
                            "Lighting/Casters", NULL, NULL);
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

            // Update lamp position
            float radius = 2.0f;
            float lampx = sin(currentFrame) * radius;
            float lampy = 0.25f;
            float lampz = cos(currentFrame) * radius;
            lampTransform.pos = vec3_make(lampx, lampy, lampz);

            vec3 diffuseColor = vec3_make(1.0f, 1.0f, 1.0f); // decrease influence
            vec3 ambientColor = vec3_make(0.2f, 0.2f, 0.2f); // low influence

            // Update box scale (review normals issue)
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
                figureTransform.pos = vec3_add(figureTransform.pos, vec3_scale(vec3_make(1.f, 0.f, 0.f), deltaTime * 2.f));
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                figureTransform.pos = vec3_add(figureTransform.pos, vec3_scale(vec3_make(1.f, 0.f, 0.f), deltaTime * -2.f));
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
                figureTransform.pos = vec3_add(figureTransform.pos, vec3_scale(vec3_make(0.f, 0.f, 1.f), deltaTime * -2.f));
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
                figureTransform.pos = vec3_add(figureTransform.pos, vec3_scale(vec3_make(0.f, 0.f, 1.f), deltaTime * 2.f));
            //figureTransform.sca.y = sin(currentFrame) + 1.2f;
            //figureTransform.rot.x = sin(currentFrame);
            //figureTransform.rot.z = cos(currentFrame);

            // Get model for figure
            model = loglTransformGetModel(&figureTransform);
            float figureShininess = 32.f;
            float emitStrength = sin(currentFrame) + 0.4f;

            // Use the specified lightingShader
            loglShaderUse(phongShader);
            loglShaderSetMat4(phongShader, "model", model);
            loglShaderSetMat4(phongShader, "view", view);
            loglShaderSetMat4(phongShader, "projection", projection);
            loglShaderSetVec3(phongShader, "viewPos", camera.transform.pos);

            // Set light uniforms
            loglShaderSetVec3(phongShader, "light.position", lampTransform.pos);
            loglShaderSetVec3(phongShader, "light.ambient", ambientColor);
            loglShaderSetVec3(phongShader, "light.diffuse", diffuseColor);
            loglShaderSetVec3(phongShader, "light.specular", vec3_make(1.0f, 1.0f, 1.0f));

            // Set material uniforms
            loglShaderSetFloat(phongShader, "material.shininess", figureShininess);
            loglShaderSetFloat(phongShader, "material.emitStrength", emitStrength);
            loglShaderSetTextures(phongShader);

            // Draw the object
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Get model for lamp
            model = loglTransformGetModel(&lampTransform);

            // Use the specified lightingShader
            loglShaderUse(lampShader);
            loglShaderSetMat4(lampShader, "model", model);
            loglShaderSetMat4(lampShader, "view", view);
            loglShaderSetMat4(lampShader, "projection", projection);

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
    glfwTerminate();
    return excode;
}
