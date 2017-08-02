#ifndef LOGL_TEXTURE_H
#define LOGL_TEXTURE_H
#include <glad/glad.h>

typedef struct _loglTexture {
    GLuint id;
    GLuint width;
    GLuint height;
    GLchar *data;
    const GLchar *name;
} loglTexture;

typedef struct _loglTexNode {
    struct _loglTexNode *next;
    struct _loglTexNode *prev;
    loglTexture *tex;
} loglTextureNode;

typedef struct _loglTexList {
    loglTextureNode *first;
    loglTextureNode *last;
    GLuint count;
} loglTextureList;

GLboolean loglTextureLoad(loglTexture *tex, const GLchar *name);
void loglTextureBind(loglTexture *tex);
void loglTextureUnload(loglTexture *tex);

void loglTextureListInit(loglTextureList *list);
loglTextureNode *loglTextureListGet(loglTextureList *list, GLuint unit);
GLuint loglTextureListAdd(loglTextureList *list, loglTexture *tex);
void loglTextureListDel(loglTextureList *list, GLuint unit);
void loglTextureListUnload(loglTextureList *list);

#endif
