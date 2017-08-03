#ifndef LOGL_SHADER_H
#define LOGL_SHADER_H
#include <string.h>
#include <glad/glad.h>
#include <lmath/lmath.h>
#include <texture.h>

typedef struct _loglShader {
    GLuint id;
    const GLchar *name;
    loglTextureList *textures;
} loglShader;

GLboolean loglShaderLoad(loglShader *shader, const GLchar *name);
void loglShaderUnload(loglShader *shader);

void loglShaderUse(loglShader shader);
void loglShaderSetMat4(loglShader shader, const GLchar *name, mat4 mat);
void loglShaderSetVec3(loglShader shader, const GLchar *name, vec3 vec);
void loglShaderSetVec2(loglShader shader, const GLchar *name, vec2 vec);
void loglShaderSetFloat(loglShader shader, const GLchar *name, GLfloat value);
void loglShaderSetInt(loglShader shader, const GLchar *name, GLint value);

GLuint loglShaderAddTexture(loglShader shader, loglTexture *tex);
void loglShaderDelTexture(loglShader shader, GLuint);
void loglShaderSetTextures(loglShader shader);

#endif
