#include <glad/glad.h>
#include <texture.h>
#include <logl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

GLboolean loglTextureLoad(loglTexture *tex, const GLchar *name) {
    const GLchar *basename = "assets/%s.png";
    const size_t basesize = strlen(basename)-2;
    const size_t namesize = strlen(name);
    const size_t concatsize = (basesize + namesize + 1) * sizeof(GLchar);
    GLchar *filename = malloc(concatsize);
    memset(filename, 0, concatsize);
    sprintf(filename, basename, name);

    GLchar *texdata = NULL;
    GLuint texw, texh;
    if (GL_FALSE == loglLoadPNG(filename, &texdata, &texw, &texh)) {
        return GL_FALSE;
    }

    free(filename);
    tex->name = name;
    tex->data = texdata;
    tex->width = texw;
    tex->height = texh;
    return GL_TRUE;
}

void loglTextureBind(loglTexture *tex) {
    // Create textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void loglTextureUnload(loglTexture *tex) {
    if (tex->data != NULL) {
        loglUnloadPNG(tex->data);
    }
}

void loglTextureListInit(loglTextureList *list) {
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
}

loglTextureNode *loglTextureListGet(loglTextureList *list, GLuint unit) {
    loglTextureNode *node = list->first;
    for (int i=0;i<unit && node != NULL;i++)
        node = node->next;

    return node;
}

GLuint loglTextureListAdd(loglTextureList *list, loglTexture *tex) {
    loglTextureNode *last = list->last;
    loglTextureNode *new = malloc(sizeof(loglTextureNode));
    new->tex = tex;
    new->next = NULL;
    new->prev = last;

    last->next = new;
    list->last = new;
    list->count++;
}

void loglTextureListDel(loglTextureList *list, GLuint unit) {
    loglTextureNode *node = loglTextureListGet(list, unit);
    if (node != NULL) {
        loglTextureNode *prev = node->prev;
        if (prev != NULL) {
            node->prev->next = node->next;
        }

        list->count--;
        free(node);
    }
}

void loglTextureListUnload(loglTextureList *list) {
    loglTextureNode *node = list->first;
    for (int i=0;i<list->count && node != NULL;i++)
        free(node);
}
