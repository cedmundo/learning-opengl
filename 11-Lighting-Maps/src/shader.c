#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <logl.h>
#include <shader.h>
#include <texture.h>
#include <lmath/lmath.h>

GLboolean loglShaderLoad(loglShader *shader, const GLchar *name) {
    GLboolean excode;
    const GLchar *vertbase = "assets/%s.vert";
    const GLchar *fragbase = "assets/%s.frag";
    const size_t basesize = strlen(vertbase)-2;
    const size_t namesize = strlen(name);
    const size_t concatsize = (basesize + namesize + 1) * sizeof(GLchar);
    GLchar *vertname = malloc(concatsize);
    GLchar *fragname = malloc(concatsize);
    memset(vertname, 0, concatsize);
    memset(fragname, 0, concatsize);
    sprintf(vertname, vertbase, name);
    sprintf(fragname, fragbase, name);

    GLchar* vSource = NULL;
    GLchar* fSource = NULL;
    GLuint vShader;
    GLuint fShader;

    if (GL_FALSE == (excode = loglLoadText(vertname, &vSource))) {
        vSource = 0; goto finalize;
    }

    if (GL_FALSE == (excode = loglCompileShaderStr(&vShader, GL_VERTEX_SHADER, vSource))) {
        vShader = 0; goto finalize;
    }

    if (GL_FALSE == (excode = loglLoadText(fragname, &fSource))) {
        fSource = 0; goto finalize;
    }

    if (GL_FALSE == (excode = loglCompileShaderStr(&fShader, GL_FRAGMENT_SHADER, fSource))) {
        fShader = 0; goto finalize;
    }

    // Create shader program
    GLuint shaderProgram;
    if (GL_FALSE == (excode = loglGetShaderProgram(&shaderProgram, vShader, fShader))) {
        goto finalize;
    }

    shader->id = shaderProgram;
    shader->name = name;
    shader->textures = malloc(sizeof(loglTextureList));
    loglTextureListInit(shader->textures);

finalize:
    if (vertname != 0)
        free(vertname);

    if (fragname != 0)
        free(fragname);

    if (vSource != 0)
        loglUnloadText(vSource);

    if (fSource != 0)
        loglUnloadText(fSource);

    if (vShader != 0)
        glDeleteShader(vShader);

    if (fShader != 0)
        glDeleteShader(fShader);

    return excode;
}

void loglShaderUnload(loglShader *shader) {
    loglTextureListUnload(shader->textures);
}

void loglShaderUse(loglShader shader) {
    glUseProgram(shader.id);
}

void loglShaderSetMat4(loglShader shader, const GLchar *name, mat4 mat) {
    glUniformMatrix4fv(glGetUniformLocation(shader.id, name), 1, GL_FALSE, mat.raw);
}

void loglShaderSetVec3(loglShader shader, const GLchar *name, vec3 vec) {
    glUniform3fv(glGetUniformLocation(shader.id, name), 1, vec.xyz);
}

void loglShaderSetVec2(loglShader shader, const GLchar *name, vec2 vec) {
    glUniform2fv(glGetUniformLocation(shader.id, name), 1, vec.xy);
}

void loglShaderSetFloat(loglShader shader, const GLchar *name, GLfloat value) {
    glUniform1fv(glGetUniformLocation(shader.id, name), 1, &value);
}

GLuint loglShaderAddTexture(loglShader shader, loglTexture *tex) {
    return loglTextureListAdd(shader.textures, tex);
}

void loglShaderDelTexture(loglShader shader, GLuint unit) {
    loglTextureListDel(shader.textures, unit);
}

void loglShaderSetTextures(loglShader shader) {
    loglTextureNode *node = shader.textures->first;
    for(unsigned int i=0;i<shader.textures->count && node != NULL;i++) {
        if (node->tex == NULL)
            continue;

        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, node->tex->id);
        glUniform1i(glGetUniformLocation(shader.id, node->tex->sampler), i);
        node = node->next;
    }
}

