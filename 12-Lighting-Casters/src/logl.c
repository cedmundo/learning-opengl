#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logl.h>
#include <png.h>

void loglProcessInput(GLFWwindow *window) {
    static GLboolean pressed0 = GL_FALSE;
    static GLboolean pressed1 = GL_FALSE;

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

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_1)) {
        pressed1 = GL_TRUE;
    } else if (GLFW_RELEASE == glfwGetKey(window, GLFW_KEY_1) && GL_TRUE == pressed1) {
        GLint value = glfwGetInputMode(window, GLFW_CURSOR);
        if (GLFW_CURSOR_NORMAL == value) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        pressed1 = GL_FALSE;
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

GLboolean loglLoadPNG(const GLchar *filename, GLchar **data, GLuint* width, GLuint* height) {
    GLboolean estatus = GL_TRUE;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("[ERROR] Could not open file: %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    // Read header
    png_byte header[8];
    if (fread(header, 1, sizeof(header), file) < 8) {
        printf("[ERROR] File is too short to be a png file: %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    if (0 == png_check_sig(header, 8)) {
        printf("[ERROR] File is not a png file: %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    // Create read struct
    png_struct *pngHandler = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (pngHandler == NULL) {
        printf("[ERROR] Failed to read PNG (maybe incorrect format): %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    // Info struct
    png_infop pngInfo = png_create_info_struct(pngHandler);
    if (pngInfo == NULL) {
        printf("[ERROR] [1] Failed to read PNG data from %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    // Exception handling code
    if(setjmp(png_jmpbuf(pngHandler))) {
        printf("[ERROR] [3] Failed to read PNG data from %s\n", filename);
        estatus = GL_FALSE; goto finalize;
    }

    png_init_io(pngHandler, file); // Init input/output
    png_set_sig_bytes(pngHandler, sizeof(header)); // Shift header
    png_read_info(pngHandler, pngInfo); // Read info structure

    int bitDepth, colorType;
    png_uint_32 tmpWidth, tmpHeight;

    // Get bit depth, color type, height and width
    png_get_IHDR(pngHandler, pngInfo, &tmpWidth, &tmpHeight, &bitDepth, &colorType, NULL, NULL, NULL);
    if (width != NULL) {
        *width = tmpWidth;
    }

    if (height != NULL) {
        *height = tmpHeight;
    }

    png_read_update_info(pngHandler, pngInfo);
    printf("[INFO][LOADING] Image %s, %lux%lu @%d\n", filename, tmpWidth, tmpHeight, bitDepth);

    // Row size in bytes
    int rowbytes = png_get_rowbytes(pngHandler, pngInfo);

    // Allocate image in a big block
    size_t blocksize = rowbytes * tmpHeight * sizeof(png_byte);
    png_byte *imageData = NULL;
    imageData = malloc(blocksize);
    if (imageData == NULL) {
        printf("[ERROR] Failed to load PNG data to memory: %s (%ld bytes)\n", filename, blocksize);
        estatus = GL_FALSE; goto finalize;
    }

    // Rowpointers is for pointing to image_data for reading the png with libpng.
    png_bytep *rowPointers = NULL;
    rowPointers = malloc(tmpHeight * sizeof(png_bytep));
    if (rowPointers == NULL) {
        printf("[ERROR] Failed to load PNG data to memory: %s (aux %ld bytes)\n", filename, tmpHeight * sizeof(png_bytep));
        estatus = GL_FALSE; goto finalize;
    }

    // Prepare rowpointers to point to imageData.
    for (int i=0;i<tmpHeight;i++) {
        rowPointers[tmpHeight - 1 - i] = imageData + i * rowbytes;
    }

    // Read full image into rowPointers (and thus, imageData)
    png_read_image(pngHandler, rowPointers);

    // Output loaded image data
    *data = imageData;
finalize:
    if (pngHandler != NULL) {
        png_destroy_read_struct(&pngHandler, &pngInfo, NULL);
    }

    if (rowPointers != NULL) {
        free(rowPointers);
    }

    if (file != NULL) {
        fclose(file);
    }

    return estatus;
}

void loglUnloadPNG(GLchar *data) {
    free(data);
}
