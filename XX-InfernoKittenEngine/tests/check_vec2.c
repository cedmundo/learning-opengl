#include <stdlib.h>
#include <check.h>
#include <ike/vec2.h>
#include "vec2_helper.h"

START_TEST(test_vec2_access)
{
    vec2 a = vec2_make(.5f, 5.f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec2_make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec2_make");
    ck_assert_msg(a.xy[0] == .5f, "Array member 0 of vector should be as same as asigned on vec2_make");
    ck_assert_msg(a.xy[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec2_make");
}
END_TEST

START_TEST(test_vec2_add)
{
    vec2 a = vec2_make(.5f, 5.f);
    vec2 b = vec2_make(.5f, 5.f);
    vec2 e = vec2_make(1.f, 10.f);
    vec2 c = vec2_add(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(-.5f,  5.f);
    b = vec2_make( .5f, -5.f);
    e = vec2_make( 0.f,  0.f);
    c = vec2_add(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(-.5f, -5.f);
    b = vec2_make(-.5f, -5.f);
    e = vec2_make(-1.f, -10.f);
    c = vec2_add(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2_sub)
{
    vec2 a = vec2_make(1.f, 10.f);
    vec2 b = vec2_make(.5f, 5.f);
    vec2 e = vec2_make(.5f, 5.f);
    vec2 c = vec2_sub(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(-.5f,  5.f);
    b = vec2_make( .5f, -5.f);
    e = vec2_make(-1.f, 10.f);
    c = vec2_sub(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(-.5f, -5.f);
    b = vec2_make(-.5f, -5.f);
    e = vec2_make(0.f, 0.f);
    c = vec2_sub(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2_scale)
{
    float b = 3.f;
    vec2 a = vec2_make(1.f, 10.f);
    vec2 e = vec2_make(3.f, 30.f);

    vec2 c = vec2_scale(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(1.f, 10.f);
    b = -3.f;
    e = vec2_make(-3.f, -30.f);
    c = vec2_scale(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2_make(-1.f, -10.f);
    b = -3.f;
    e = vec2_make(3.f, 30.f);
    c = vec2_scale(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2_mul_inner)
{
    vec2 a = vec2_make(2.f, 10.f);
    vec2 b = vec2_make(3.f, 2.f);
    float e = 26.f;
    float c = vec2_mul_inner(a, b);
    ck_assert(c == e);

    // TODO: Negative cases
}
END_TEST

START_TEST(test_vec2_sqr_len)
{
    vec2 a = vec2_make(2.f, 2.f);
    float e = 8.f;
    float c = vec2_sqr_len(a);
    ck_assert(c == e);

    // TODO: Negative cases
}
END_TEST

START_TEST(test_vec2_len)
{
    vec2 a = vec2_make(2.f, 2.f);
    float e = sqrtf(8.f);
    float c = vec2_len(a);
    ck_assert(c == e);

    // TODO: Negative cases
}
END_TEST

START_TEST(test_vec2_norm)
{
    vec2 a = vec2_make(1.f, 1.f);
    vec2 e = vec2_make(1.f, 1.f);
    vec2 c = vec2_norm(a);
    ck_assert_vec2_eq(c, e);

    // TODO: Negative cases
}
END_TEST

START_TEST(test_vec2_min)
{
    vec2 a = vec2_make(3.f, 6.f);
    vec2 b = vec2_make(2.f, 8.f);
    vec2 e = vec2_make(2.f, 6.f);
    vec2 c = vec2_min(a, b);
    ck_assert_vec2_eq(c, e);

    // TODO: Negative cases
}
END_TEST

START_TEST(test_vec2_max)
{
    vec2 a = vec2_make(3.f, 6.f);
    vec2 b = vec2_make(2.f, 8.f);
    vec2 e = vec2_make(3.f, 8.f);
    vec2 c = vec2_max(a, b);
    ck_assert_vec2_eq(c, e);

    // TODO: Negative cases
}
END_TEST

/*
 * Vec2 Testing suite.
 */
Suite *vec2_suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access;

    s = suite_create("ike/vec2");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec2_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec2_add);
    tcase_add_test(tc_arithm, test_vec2_sub);
    tcase_add_test(tc_arithm, test_vec2_scale);
    tcase_add_test(tc_arithm, test_vec2_mul_inner);
    tcase_add_test(tc_arithm, test_vec2_sqr_len);
    tcase_add_test(tc_arithm, test_vec2_len);
    tcase_add_test(tc_arithm, test_vec2_norm);
    tcase_add_test(tc_arithm, test_vec2_min);
    tcase_add_test(tc_arithm, test_vec2_max);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec2_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
