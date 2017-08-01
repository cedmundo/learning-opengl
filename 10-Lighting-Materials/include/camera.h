#ifndef LOGL_CAMERA_H
#define LOGL_CAMERA_H
#include <lmath/vec3.h>
#include <lmath/mat4.h>
#include "transform.h"
#include <GLFW/glfw3.h>

typedef struct _loglCamera {
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float fov;
    float aspect;
    float near;
    float far;
    float winWidth;
    float winHeight;

    vec2 lastMousePos;
    int isFirstMouse;

    loglTransform transform;
    GLFWwindow *window;
} loglCamera;

void loglCameraInit(loglCamera *, GLFWwindow *);
void loglCameraUpdate(loglCamera *, float dt);
mat4 loglCameraGetView(loglCamera const *);
mat4 loglCameraGetProjection(loglCamera const *);

#endif
