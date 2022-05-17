//
// Created by Carlos on 16/05/2022.
//

#ifndef LEARNING_OPENGL_UTILS_H
#define LEARNING_OPENGL_UTILS_H
#include <stdio.h>

char *load_text_file(const char *name);
void unload_text_file(char *);

#define CHECK_TEXT_FILE_ERROR(data, file) do {           \
    if ((data) == NULL) {                                \
        fprintf(stderr, "cannot load file: " file "\n"); \
        exit_code = -1;                                  \
        goto terminate;                                  \
    }                                                    \
} while(0)

#define CHECK_SHADER_COMPILE_ERROR(shader_id) do {                      \
    GLint success = 0;                                                  \
    char compile_log[512] = {0};                                        \
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);              \
    if (!success) {                                                     \
        glGetShaderInfoLog(shader_id, 512, NULL, compile_log);          \
        fprintf(stderr, "error compiling shader: %s\n", compile_log);   \
        exit_code = -1;                                                 \
        goto terminate;                                                 \
    }                                                                   \
} while(0)

#define CHECK_SHADER_LINK_ERROR(program_id) do {                    \
    GLint success = 0;                                              \
    char link_log[512] = {0};                                       \
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);           \
    if (!success) {                                                 \
        glGetShaderInfoLog(program_id, 512, NULL, link_log);        \
        fprintf(stderr, "error linking shader: %s\n", link_log);    \
        exit_code = -1;                                             \
        goto terminate;                                             \
    }                                                               \
} while(0)

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif linux
#include <unistd.h>
#define GetCurrentDir getcwd
#else
#error "Unknown target OS"
#endif

#endif //LEARNING_OPENGL_UTILS_H
