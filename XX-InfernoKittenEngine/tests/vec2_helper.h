#ifndef IKETESTING_VEC2_HELPER_H
#define IKETESTING_VEC2_HELPER_H
#include <check.h>

static inline int ck_assert_vec2_eq(vec2 a, vec2 b) {
    int xe, ye;
    ck_assert_msg(xe = (a.x == b.x), "x member of a and b are not equal");
    ck_assert_msg(ye = (a.y == b.y), "y member of a and b are not equal");
    return xe == 1 && ye == 1;
}

#endif /* IKETESTING_VEC2_HELPER_H */

