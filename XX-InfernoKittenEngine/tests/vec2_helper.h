#ifndef IKETESTING_VEC2_HELPER_H
#define IKETESTING_VEC2_HELPER_H
#include <check.h>

static inline int ck_assert_vec2_eq(vec2 a, vec2 b) {
    int xe, ye;
    float ax = ceilf(a.x * 100.f)/100.f;
    float ay = ceilf(a.y * 100.f)/100.f;
    float bx = ceilf(b.x * 100.f)/100.f;
    float by = ceilf(b.y * 100.f)/100.f;

    ck_assert_msg(xe = (ax == bx), "x member of a and b are not equal");
    ck_assert_msg(ye = (ay == by), "y member of a and b are not equal");
    return xe == 1 && ye == 1;
}

#endif /* IKETESTING_VEC2_HELPER_H */

