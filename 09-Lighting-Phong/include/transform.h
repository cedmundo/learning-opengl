#ifndef LOGL_TRANSFORM_H
#define LOGL_TRANSFORM_H
#include <lmath/vec3.h>
#include <lmath/mat4.h>

typedef struct _loglTransform {
    vec3 sca;
    vec3 pos;
    vec3 rot;
} loglTransform;

mat4 loglTransformGetModel(loglTransform *);

#endif
