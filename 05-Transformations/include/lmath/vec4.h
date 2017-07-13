#ifndef LMATH_VEC3_H
#define LMATH_VEC3_H
#include <math.h>
#include "vec2.h"
#include "vec3.h"

typedef union {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float xy[2];
    float xyz[3];
    float xyzw[4];
} vec4;

static const vec4 vec3_zero = {0.0f, 0.0f, 0.0f, 0.0f};
static const vec4 vec3_one = {1.0f, 1.0f, 1.0f, 1.0f};

static inline vec4 vec4_make(float x, float y, float z, float w) {
    vec3 r;
    r.x = x;
    r.y = y;
    r.z = z;
    r.w = w;
    return r;
}

static inline vec4 vec4_make1(vec2 v, float z, float w) {
    vec4 r;
    r.x = v.x;
    r.y = v.y;
    r.z = z;
    r.w = w;
    return r;
}

static inline vec4 vec4_make2(vec3 v, float w) {
    vec4 r;
    r.x = v.x;
    r.y = v.y;
    r.z = v.z;
    r.w = w;
    return r;
}

static inline vec4 vec4_add(const vec4 a, const vec4 b) {
    vec4 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    r.w = a.w + b.w;
    return r;
}

static inline vec4 vec4_sub(const vec4 a, const vec4 b) {
    vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    r.w = a.w - b.w;
    return r;
}

static inline vec4 vec4_scale(const vec4 a, const float s) {
    vec3 r;
    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    r.w = a.w * s;
    return r;
}

static inline float vec4_mul_inner(const vec4 a, const vec4 b) {
    float r = 0.0f;
    r += a.x * b.x;
    r += a.y * b.y;
    r += a.z * b.z;
    r += a.w * b.w;
    return r;
}

static inline float vec4_sqr_len(const vec4 a) {
    return vec4_mul_inner(a, a);
}

static inline float vec4_len(const vec4 a) {
    return sqrtf(vec4_sqr_len(a));
}

static inline vec4 vec4_norm(const vec4 a) {
    float k = 1.0f / vec4_len(a);
    return vec4_scale(a, k);
}

static inline vec4 vec4_min(const vec4 a, const vec4 b) {
    vec4 r;
    r.x = a.x < b.x ? a.x : b.x;
    r.y = a.y < b.y ? a.y : b.y;
    r.z = a.z < b.z ? a.z : b.z;
    r.w = a.w < b.w ? a.w : b.w;
    return r;
}

static inline vec4 vec4_max(const vec4 a, const vec4 b) {
    vec4 r;
    r.x = a.x > b.x ? a.x : b.x;
    r.y = a.y > b.y ? a.y : b.y;
    r.z = a.z > b.z ? a.z : b.z;
    r.w = a.w > b.w ? a.w : b.w;
    return r;
}

static inline vec4 vec4_mul_cross(const vec4 a, const vec4 b) {
    vec4 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    r.w = 1.0f;
    return r;
}

static inline vec4 vec4_reflect(const vec4 a, const vec4 b) {
    float p = 2.0f * vec4_mul_inner(a, b);
    vec3 r;
    r.x = a.x - b.x * p;
    r.y = a.y - b.y * p;
    r.z = a.z - b.z * p;
    r.w = a.w - b.w * p;
    return r;
}

#endif
