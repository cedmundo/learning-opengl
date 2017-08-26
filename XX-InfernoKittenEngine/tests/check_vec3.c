#include <stdlib.h>
#include <check.h>
#include <ike/vec3.h>
#include "vec3_helper.h"

START_TEST(test_vec3_access)
{
    vec3 a = vec3_make(.5f, 5.f, -5.f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec3_make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec3_make");
    ck_assert_msg(a.z == -5.f, "Z Member of vector should be as same as asigned on vec3_make");
    ck_assert_msg(a.xyz[0] == .5f, "Array member 0 of vector should be as same as asigned on vec3_make");
    ck_assert_msg(a.xyz[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec3_make");
    ck_assert_msg(a.xyz[2] == -5.f, "Array member 2 of vector should be as same as asigned on vec3_make");
}
END_TEST

START_TEST(test_vec3_add)
{
    vec3 a = vec3_make(.5f, 5.f, -5.f);
    vec3 b = vec3_make(.5f, 5.f, -5.f);
    vec3 e = vec3_make(1.f, 10.f, -10.f);
    vec3 c = vec3_add(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-.5f, -5.f, 5.f);
    b = vec3_make(.5f, 5.f, -5.f);
    e = vec3_make(0.f, 0.f, 0.f);
    c = vec3_add(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_sub)
{
    vec3 a = vec3_make(.5f, 5.f, -5.f);
    vec3 b = vec3_make(.5f, 5.f, -5.f);
    vec3 e = vec3_make(0.f, 0.f, 0.f);
    vec3 c = vec3_sub(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(6.f, 4.f, 5.f);
    b = vec3_make(5.f, 2.f, 2.f);
    e = vec3_make(1.f, 2.f, 3.f);
    c = vec3_sub(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-.5f, 5.f, 5.f);
    b = vec3_make(.5f, 2.f, -5.f);
    e = vec3_make(-1.f, 3.f, 10.f);
    c = vec3_sub(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_scale)
{
    vec3 a = vec3_make(.5f, 5.f, -5.f);
    float b = 3.f;
    vec3 e = vec3_make(1.5f, 15.f, -15.f);
    vec3 c = vec3_scale(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(6.f, 4.f, 5.f);
    b = 3.f;
    e = vec3_make(18.f, 12.f, 15.f);
    c = vec3_scale(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-.5f, 5.f, -5.f);
    b = -2.f;
    e = vec3_make(1.f, -10.f, 10.f);
    c = vec3_scale(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_mul_inner)
{
    vec3 a = vec3_make(2.f, 10.f, 3.f);
    vec3 b = vec3_make(3.f, 2.f, 5.f);
    float e = 41.f;
    float c = vec3_mul_inner(a, b);
    ck_assert(c == e);

    a = vec3_make(-2.f, 10.f, .3f);
    b = vec3_make(3.f, 2.f, 2.f);
    e = 14.6f;
    c = vec3_mul_inner(a, b);
    ck_assert(c == e);

    a = vec3_make(2.f, -10.f, 0.f);
    b = vec3_make(3.f, 2.f, 10.f);
    e = -14.f;
    c = vec3_mul_inner(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3_sqr_len)
{
    float e = 12.f;

    vec3 a = vec3_make(2.f, 2.f, 2.f);
    float c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, -2.f, 2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(2.f, -2.f, 2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, 2.f, 2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, -2.f, -2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(2.f, -2.f, -2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, 2.f, -2.f);
    c = vec3_sqr_len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3_len)
{
    float e = sqrtf(12.f);

    vec3 a = vec3_make(2.f, 2.f, 2.f);
    float c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, -2.f, 2.f);
    c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(2.f, -2.f, 2.f);
    c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, 2.f, 2.f);
    c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, -2.f, -2.f);
    c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(2.f, -2.f, -2.f);
    c = vec3_len(a);
    ck_assert(c == e);

    a = vec3_make(-2.f, 2.f, -2.f);
    c = vec3_len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3_norm)
{
    vec3 a = vec3_make(2.f, 2.f, 2.f);
    vec3 e = vec3_make(1.f/sqrtf(3.f), 1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    vec3 c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-2.f, -2.f, 2.f);
    e = vec3_make(-1.f/sqrtf(3.f), -1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(2.f, -2.f, 2.f);
    e = vec3_make(1.f/sqrtf(3.f), -1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-2.f, 2.f, 2.f);
    e = vec3_make(-1.f/sqrtf(3.f), 1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-2.f, -2.f, -2.f);
    e = vec3_make(-1.f/sqrtf(3.f), -1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(2.f, -2.f, -2.f);
    e = vec3_make(1.f/sqrtf(3.f), -1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-2.f, 2.f, -2.f);
    e = vec3_make(-1.f/sqrtf(3.f), 1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3_norm(a);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_min)
{
    vec3 a = vec3_make(3.f, 6.f, 4.f);
    vec3 b = vec3_make(2.f, 8.f, 2.f);
    vec3 e = vec3_make(2.f, 6.f, 2.f);
    vec3 c = vec3_min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-3.f, 6.f, -1.f);
    b = vec3_make(2.f, 8.f, -1.f);
    e = vec3_make(-3.f, 6.f, -1.f);
    c = vec3_min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(3.f, -6.f, 3.f);
    b = vec3_make(2.f, 8.f, -3.f);
    e = vec3_make(2.f, -6.f,-3.f);
    c = vec3_min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(3.f, -6.f,-2.f);
    b = vec3_make(2.f, -8.f, 2.f);
    e = vec3_make(2.f, -8.f,-2.f);
    c = vec3_min(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_max)
{
    vec3 a = vec3_make(3.f, 6.f, 5.f);
    vec3 b = vec3_make(2.f, 8.f, 7.f);
    vec3 e = vec3_make(3.f, 8.f, 7.f);
    vec3 c = vec3_max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-3.f, 6.f, 3.f);
    b = vec3_make(2.f, 8.f, -3.f);
    e = vec3_make(2.f, 8.f, 3.f);
    c = vec3_max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(2.f, -6.f, 1.f);
    b = vec3_make(4.f, 8.f, 1.f);
    e = vec3_make(4.f, 8.f, 1.f);
    c = vec3_max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(3.f, -6.f, -3.f);
    b = vec3_make(2.f, -8.f, -2.f);
    e = vec3_make(3.f, -6.f, -2.f);
    c = vec3_max(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_dot)
{
    vec3 a = vec3_make(1.f, 2.f, 3.f);
    vec3 b = vec3_make(4.f, 5.f, 6.f);
    float e = 32.f;
    float c = vec3_dot(a, b);
    ck_assert(c == e);

    a = vec3_make(1.f, -2.f, 3.f);
    b = vec3_make(-4.f, 5.f, -6.f);
    e = -32.f;
    c = vec3_dot(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3_cross)
{
    vec3 a = vec3_make(1.f, 2.f, 3.f);
    vec3 b = vec3_make(4.f, 5.f, 6.f);
    vec3 e = vec3_make(-3.f, 6.f, -3.f);
    vec3 c = vec3_cross(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-1.f, 2.f, -3.f);
    b = vec3_make(4.f, -5.f, 6.f);
    e = vec3_make(-3.f, -6.f, -3.f);
    c = vec3_cross(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3_reflect)
{
    vec3 a = vec3_make(1.f, 2.f, 3.f);
    vec3 b = vec3_make(4.f, 5.f, 6.f);
    vec3 e = vec3_make(-2.32468f, -2.15584f, -1.98701f);
    vec3 c = vec3_reflect(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3_make(-2.f, 3.f, -6.f);
    b = vec3_make(1.f, -4.f, 5.f);
    e = vec3_make(0.0952381f, -5.38095f, 4.47619f);
    c = vec3_reflect(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

/*
 * Vec3 Testing suite.
 */
Suite *vec3_suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_make;

    s = suite_create("ike/vec3");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec3_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec3_add);
    tcase_add_test(tc_arithm, test_vec3_sub);
    tcase_add_test(tc_arithm, test_vec3_scale);
    tcase_add_test(tc_arithm, test_vec3_mul_inner);
    tcase_add_test(tc_arithm, test_vec3_sqr_len);
    tcase_add_test(tc_arithm, test_vec3_len);
    tcase_add_test(tc_arithm, test_vec3_norm);
    tcase_add_test(tc_arithm, test_vec3_min);
    tcase_add_test(tc_arithm, test_vec3_max);
    tcase_add_test(tc_arithm, test_vec3_dot);
    tcase_add_test(tc_arithm, test_vec3_cross);
    tcase_add_test(tc_arithm, test_vec3_reflect);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec3_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

