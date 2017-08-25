#ifndef IKE_VEC2_H
#define IKE_VEC2_H
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

#endif /* IKE_VEC2_H */
