#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>

void loglProcessInput(GLFWwindow *window) {
    static GLboolean pressed0 = GL_FALSE;

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_0)) {
        pressed0 = GL_TRUE;
    } else if (GLFW_RELEASE == glfwGetKey(window, GLFW_KEY_0) && GL_TRUE == pressed0) {
        GLint pmode[2];
        glGetIntegerv(GL_POLYGON_MODE, pmode);

        if (GL_POINT == pmode[1]) {
            printf("[INFO] Fill mode\n");
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else if (GL_LINE == pmode[1]) {
            printf("[INFO] Point mode\n");
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        } else {
            printf("[INFO] Line mode\n");
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        pressed0 = GL_FALSE;
    }
}

void loglResizeCb(GLFWwindow *window, GLint width, GLint height) {
    glViewport(0, 0, width, height);
}

GLboolean loglCompileShaderStr(GLuint* outShaderId, GLint type, const GLchar* source) {
    // Compile vertex shader
    GLuint shaderId;
    shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &source, NULL);
    glCompileShader(shaderId);

    // Check compilation status
    GLint compileSuccess;
    GLchar compileLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);
    if (GL_FALSE == compileSuccess) {
        glGetShaderInfoLog(shaderId, 512, NULL, compileLog);
        printf("[ERROR] %s shader compilation failed: %s\n",
                (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), compileLog);
        return GL_FALSE;
    }

    *outShaderId = shaderId;
    return GL_TRUE;
}

GLboolean loglGetShaderProgram(GLuint *outProgramId, GLuint vShader, GLuint fShader) {
    // Create the program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    // Check linkage errors
    GLint compileSuccess;
    GLchar compileLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compileSuccess);
    if (GL_FALSE == compileSuccess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, compileLog);
        printf("[ERROR] Shader program linkage error: %s\n", compileLog);
        return GL_FALSE;
    }

    *outProgramId = shaderProgram;
    return GL_TRUE;
}

GLboolean loglLoadText(const GLchar *filename, GLchar **data) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("[ERROR] Could not open file: %s\n", filename);
        return GL_FALSE;
    }

    fseek (file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    *data = malloc (sizeof(char) * (size+1));
    if (*data == NULL) {
        printf("[ERROR] (Severe) Could not allocate enought memory for file: %s\n", filename);
        return GL_FALSE;
    }

    size_t rres = fread(*data, 1, size, file);
    if (rres != size) {
        printf("[ERROR] Reading file error: %s\n", filename);
        return GL_FALSE;
    }

    (*data)[size] = 0;
    fclose(file);
    return GL_TRUE;
}

void loglUnloadText(GLchar *data) {
    free(data);
}
