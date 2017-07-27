#ifndef LOGL_CAMERA_H
#define LOGL_CAMERA_H
#include <lmath/vec3.h>
#include <lmath/mat4.h>
#include "transform.h"

typedef struct _loglCamera {
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    loglTransform transform;
} loglCamera;

#endif
