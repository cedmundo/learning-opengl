#include <stdlib.h>
#include <check.h>
#include <ike/vec4.h>
#include "vec4_helper.h"

START_TEST(test_vec4_access)
{
    vec4 a = vec4_make(.5f, 5.f, -5.f, -.5f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.z == -5.f, "Z Member of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.w == -.5f, "W Member of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.xyzw[0] == .5f, "Array member 0 of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.xyzw[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.xyzw[2] == -5.f, "Array member 2 of vector should be as same as asigned on vec4_make");
    ck_assert_msg(a.xyzw[3] == -.5f, "Array member 3 of vector should be as same as asigned on vec4_make");
}
END_TEST

START_TEST(test_vec4_add)
{
    vec4 a = vec4_make(.5f, 5.f, -5.f, -.5f);
    vec4 b = vec4_make(.5f, 5.f, -5.f, -.5f);
    vec4 e = vec4_make(1.f, 10.f, -10.f, -1.f);
    vec4 c = vec4_add(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-.5f, -5.f, 5.f, -.5f);
    b = vec4_make(.5f, 5.f, -5.f, -.5f);
    e = vec4_make(0.f, 0.f, 0.f, -1.f);
    c = vec4_add(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4_sub)
{
    vec4 a = vec4_make(.5f, 5.f, -5.f, -.5f);
    vec4 b = vec4_make(.5f, 5.f, -5.f, -.5f);
    vec4 e = vec4_make(0.f, 0.f, 0.f, 0.f);
    vec4 c = vec4_sub(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(6.f, 4.f, 5.f, 8.f);
    b = vec4_make(5.f, 2.f, 2.f, 2.f);
    e = vec4_make(1.f, 2.f, 3.f, 6.f);
    c = vec4_sub(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-.5f, 5.f, 5.f, -.5f);
    b = vec4_make(.5f, 2.f, -5.f, 3.f);
    e = vec4_make(-1.f, 3.f, 10.f, 2.5f);
    c = vec4_sub(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4_scale)
{
    vec4 a = vec4_make(.5f, 5.f, -5.f, -.5f);
    float b = 3.f;
    vec4 e = vec4_make(1.5f, 15.f, -15.f, -1.f);
    vec4 c = vec4_scale(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(6.f, 4.f, 5.f, 1.f);
    b = 3.f;
    e = vec4_make(18.f, 12.f, 15.f, 3.f);
    c = vec4_scale(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-.5f, 5.f, -5.f, -.5f);
    b = -2.f;
    e = vec4_make(1.f, -10.f, 10.f, 1.f);
    c = vec4_scale(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4_mul_inner)
{
    vec4 a = vec4_make(2.f, 10.f, 3.f, 2.f);
    vec4 b = vec4_make(3.f, 2.f, 5.f, 1.f);
    float e = 43.f;
    float c = vec4_mul_inner(a, b);
    ck_assert(c == e);

    a = vec4_make(-2.f, 10.f, .3f, 3.f);
    b = vec4_make(3.f, 2.f, 2.f, 2.f);
    e = 20.6f;
    c = vec4_mul_inner(a, b);
    ck_assert(c == e);

    a = vec4_make(2.f, -10.f, 0.f, -3.f);
    b = vec4_make(3.f, 2.f, 10.f, 5.f);
    e = -29.f;
    c = vec4_mul_inner(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4_sqr_len)
{
    float e = 16.f;

    vec4 a = vec4_make(2.f, 2.f, 2.f, 2.f);
    float c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, 2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, 2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, 2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, -2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, -2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, -2.f, 2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, 2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, 2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, 2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, -2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, -2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, -2.f, -2.f);
    c = vec4_sqr_len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4_len)
{
    float e = sqrtf(16.f);

    vec4 a = vec4_make(2.f, 2.f, 2.f, 2.f);
    float c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, 2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, 2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, 2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, -2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, -2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, -2.f, 2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, 2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, 2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, 2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, -2.f, -2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(2.f, -2.f, -2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);

    a = vec4_make(-2.f, 2.f, -2.f, -2.f);
    c = vec4_len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4_norm)
{
    vec4 a = vec4_make(2.f, 2.f, 2.f, 2.f);
    vec4 e = vec4_make(1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    vec4 c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, -2.f, 2.f, 2.f);
    e = vec4_make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, -2.f, 2.f, 2.f);
    e = vec4_make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, 2.f, 2.f, 2.f);
    e = vec4_make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, -2.f, -2.f, 2.f);
    e = vec4_make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, -2.f, -2.f, 2.f);
    e = vec4_make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, 2.f, -2.f, 2.f);
    e = vec4_make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, 2.f, 2.f, -2.f);
    e = vec4_make(1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, -2.f, 2.f, -2.f);
    e = vec4_make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, -2.f, 2.f, -2.f);
    e = vec4_make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, 2.f, 2.f, -2.f);
    e = vec4_make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, -2.f, -2.f, -2.f);
    e = vec4_make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, -2.f, -2.f, -2.f);
    e = vec4_make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-2.f, 2.f, -2.f, -2.f);
    e = vec4_make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4_norm(a);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4_min)
{
    vec4 a = vec4_make(3.f, 6.f, 4.f, 1.f);
    vec4 b = vec4_make(2.f, 8.f, 2.f, 1.f);
    vec4 e = vec4_make(2.f, 6.f, 2.f, 1.f);
    vec4 c = vec4_min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-3.f, 6.f, -1.f, -2.f);
    b = vec4_make(2.f, 8.f, -1.f, -3.5f);
    e = vec4_make(-3.f, 6.f, -1.f, -3.f);
    c = vec4_min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(3.f, -6.f, 3.f, 2.f);
    b = vec4_make(2.f, 8.f, -3.f, 2.f);
    e = vec4_make(2.f, -6.f,-3.f, 2.f);
    c = vec4_min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(3.f, -6.f,-2.f, 1.f);
    b = vec4_make(2.f, -8.f, 2.f, 1.f);
    e = vec4_make(2.f, -8.f,-2.f, 1.f);
    c = vec4_min(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4_max)
{
    vec4 a = vec4_make(3.f, 6.f, 5.f, 4.f);
    vec4 b = vec4_make(2.f, 8.f, 7.f, 4.f);
    vec4 e = vec4_make(3.f, 8.f, 7.f, 4.f);
    vec4 c = vec4_max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(-3.f, 6.f, 3.f, 1.f);
    b = vec4_make(2.f, 8.f, -3.f, 1.1f);
    e = vec4_make(2.f, 8.f, 3.f, 1.1f);
    c = vec4_max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(2.f, -6.f, 1.f, 3.f);
    b = vec4_make(4.f, 8.f, 1.f, 3.f);
    e = vec4_make(4.f, 8.f, 1.f, 3.f);
    c = vec4_max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4_make(3.f, -6.f, -3.f, -2.f);
    b = vec4_make(2.f, -8.f, -2.f, -2.f);
    e = vec4_make(3.f, -6.f, -2.f, -2.f);
    c = vec4_max(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

Suite *vec4_suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_make;

    s = suite_create("ike/vec4");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec4_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec4_add);
    tcase_add_test(tc_arithm, test_vec4_sub);
    tcase_add_test(tc_arithm, test_vec4_scale);
    tcase_add_test(tc_arithm, test_vec4_mul_inner);
    tcase_add_test(tc_arithm, test_vec4_sqr_len);
    tcase_add_test(tc_arithm, test_vec4_len);
    tcase_add_test(tc_arithm, test_vec4_norm);
    tcase_add_test(tc_arithm, test_vec4_min);
    tcase_add_test(tc_arithm, test_vec4_max);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec4_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

