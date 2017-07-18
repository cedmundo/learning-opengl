#ifndef LMATH_VEC3_H
#define LMATH_VEC3_H
#include <math.h>
#include "vec2.h"

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float xy[2];
    float xyz[3];
} vec3;

static const vec3 vec3_zero = {0.0f, 0.0f, 0.0f};
static const vec3 vec3_one = {1.0f, 1.0f, 1.0f};

static inline vec3 vec3_make(float x, float y, float z) {
    vec3 r;
    r.x = x;
    r.y = y;
    r.z = z;
    return r;
}

static inline vec3 vec3_make1(vec2 v, float z) {
    vec3 r;
    r.x = v.x;
    r.y = v.y;
    r.z = z;
    return r;
}

static inline vec3 vec3_add(const vec3 a, const vec3 b) {
    vec3 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

static inline vec3 vec3_sub(const vec3 a, const vec3 b) {
    vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

static inline vec3 vec3_scale(const vec3 a, const float s) {
    vec3 r;
    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    return r;
}

static inline float vec3_mul_inner(const vec3 a, const vec3 b) {
    float r = 0.0f;
    r += a.x * b.x;
    r += a.y * b.y;
    r += a.z * b.z;
    return r;
}

static inline float vec3_sqr_len(const vec3 a) {
    return vec3_mul_inner(a, a);
}

static inline float vec3_len(const vec3 a) {
    return sqrtf(vec3_sqr_len(a));
}

static inline vec3 vec3_norm(const vec3 a) {
    float k = 1.0f / vec3_len(a);
    return vec3_scale(a, k);
}

static inline vec3 vec3_min(const vec3 a, const vec3 b) {
    vec3 r;
    r.x = a.x < b.x ? a.x : b.x;
    r.y = a.y < b.y ? a.y : b.y;
    r.z = a.z < b.z ? a.z : b.z;
    return r;
}

static inline vec3 vec3_max(const vec3 a, const vec3 b) {
    vec3 r;
    r.x = a.x > b.x ? a.x : b.x;
    r.y = a.y > b.y ? a.y : b.y;
    r.z = a.z > b.z ? a.z : b.z;
    return r;
}

static inline vec3 vec3_mul_cross(const vec3 a, const vec3 b) {
    vec3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

static inline vec3 vec3_reflect(const vec3 a, const vec3 b) {
    float p = 2.0f * vec3_mul_inner(a, b);
    vec3 r;
    r.x = a.x - b.x * p;
    r.y = a.y - b.y * p;
    r.z = a.z - b.z * p;
    return r;
}

#endif
