#ifndef IKETESTING_VEC3_HELPER_H
#define IKETESTING_VEC3_HELPER_H
#include <check.h>
#include <math.h>

static inline int ck_assert_vec3_eq(vec3 a, vec3 b) {
    int xe, ye, ze;
    float ax = ceilf(a.x * 100.f)/100.f;
    float ay = ceilf(a.y * 100.f)/100.f;
    float az = ceilf(a.z * 100.f)/100.f;

    float bx = ceilf(b.x * 100.f)/100.f;
    float by = ceilf(b.y * 100.f)/100.f;
    float bz = ceilf(b.z * 100.f)/100.f;

    ck_assert_msg(xe = (ax == bx), "x member of a and b are not equal (approximated)");
    ck_assert_msg(ye = (ay == by), "y member of a and b are not equal (approximated)");
    ck_assert_msg(ze = (az == bz), "z member of a and b are not equal (approximated)");
    return xe == 1 && ye == 1 && ze == 1;
}

#endif /* IKETESTING_VEC3_HELPER_H */

