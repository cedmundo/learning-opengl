#ifndef LMATH_H
#define LMATH_H
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

static inline float lmath_radians(float value) {
    return value * 0.01745329252f;
}

static inline float lmath_maxf(float val, float max){
    return val > max ? max : val;
}

static inline float lmath_minf(float val, float max){
    return val < max ? max : val;
}

#endif
