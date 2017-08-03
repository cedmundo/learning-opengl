#ifndef LMATH_VEC2_H
#define LMATH_VEC2_H
#include <math.h>

typedef union {
    struct {
        float x;
        float y;
    };
    float xy[2];
} vec2;

static const vec2 vec2_zero = {0.0f, 0.0f};
static const vec2 vec2_one = {1.0f, 1.0f};

static inline vec2 vec2_make(float x, float y) {
    vec2 r;
    r.x = x;
    r.y = y;
    return r;
}

static inline vec2 vec2_add(const vec2 a, const vec2 b) {
    vec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

static inline vec2 vec2_sub(const vec2 a, const vec2 b) {
    vec2 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

static inline vec2 vec2_scale(const vec2 a, const float s) {
    vec2 r;
    r.x = a.x * s;
    r.y = a.y * s;
    return r;
}

static inline float vec2_mul_inner(const vec2 a, const vec2 b) {
    float r = 0.0f;
    r += a.x * b.x;
    r += a.y * b.y;
    return r;
}

static inline float vec2_sqr_len(const vec2 a) {
    return vec2_mul_inner(a, a);
}

static inline float vec2_len(const vec2 a) {
    return sqrtf(vec2_sqr_len(a));
}

static inline vec2 vec2_norm(const vec2 a) {
    float k = 1.0f / vec2_len(a);
    return vec2_scale(a, k);
}

static inline vec2 vec2_min(const vec2 a, const vec2 b) {
    vec2 r;
    r.x = a.x < b.x ? a.x : b.x;
    r.y = a.y < b.y ? a.y : b.y;
    return r;
}

static inline vec2 vec2_max(const vec2 a, const vec2 b) {
    vec2 r;
    r.x = a.x > b.x ? a.x : b.x;
    r.y = a.y > b.y ? a.y : b.y;
    return r;
}

#endif
