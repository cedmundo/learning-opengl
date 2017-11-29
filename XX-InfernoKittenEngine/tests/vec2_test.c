#include <stdlib.h>
#include <check.h>
#include <ike/vec2.h>
#include "vec2_helper.h"

START_TEST(test_vec2_access)
{
    vec2 a = vec2Make(.5f, 5.f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec2Make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec2Make");
    ck_assert_msg(a.xy[0] == .5f, "Array member 0 of vector should be as same as asigned on vec2Make");
    ck_assert_msg(a.xy[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec2Make");
}
END_TEST

START_TEST(test_vec2Add)
{
    vec2 a = vec2Make(.5f, 5.f);
    vec2 b = vec2Make(.5f, 5.f);
    vec2 e = vec2Make(1.f, 10.f);
    vec2 c = vec2Add(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-.5f,  5.f);
    b = vec2Make( .5f, -5.f);
    e = vec2Make( 0.f,  0.f);
    c = vec2Add(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-.5f, -5.f);
    b = vec2Make(-.5f, -5.f);
    e = vec2Make(-1.f, -10.f);
    c = vec2Add(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2Sub)
{
    vec2 a = vec2Make(1.f, 10.f);
    vec2 b = vec2Make(.5f, 5.f);
    vec2 e = vec2Make(.5f, 5.f);
    vec2 c = vec2Sub(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-.5f,  5.f);
    b = vec2Make( .5f, -5.f);
    e = vec2Make(-1.f, 10.f);
    c = vec2Sub(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-.5f, -5.f);
    b = vec2Make(-.5f, -5.f);
    e = vec2Make(0.f, 0.f);
    c = vec2Sub(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2Scale)
{
    float b = 3.f;
    vec2 a = vec2Make(1.f, 10.f);
    vec2 e = vec2Make(3.f, 30.f);

    vec2 c = vec2Scale(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(1.f, 10.f);
    b = -3.f;
    e = vec2Make(-3.f, -30.f);
    c = vec2Scale(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-1.f, -10.f);
    b = -3.f;
    e = vec2Make(3.f, 30.f);
    c = vec2Scale(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2MulInner)
{
    vec2 a = vec2Make(2.f, 10.f);
    vec2 b = vec2Make(3.f, 2.f);
    float e = 26.f;
    float c = vec2MulInner(a, b);
    ck_assert(c == e);

    a = vec2Make(-2.f, 10.f);
    b = vec2Make(3.f, 2.f);
    e = 14.f;
    c = vec2MulInner(a, b);
    ck_assert(c == e);

    a = vec2Make(2.f, -10.f);
    b = vec2Make(3.f, 2.f);
    e = -14.f;
    c = vec2MulInner(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec2SqrLen)
{
    float e = 8.f;

    vec2 a = vec2Make(2.f, 2.f);
    float c = vec2SqrLen(a);
    ck_assert(c == e);

    a = vec2Make(-2.f, -2.f);
    c = vec2SqrLen(a);
    ck_assert(c == e);

    a = vec2Make(2.f, -2.f);
    c = vec2SqrLen(a);
    ck_assert(c == e);

    a = vec2Make(-2.f, 2.f);
    c = vec2SqrLen(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec2Len)
{
    float e = sqrtf(8.f);

    vec2 a = vec2Make(2.f, 2.f);
    float c = vec2Len(a);
    ck_assert(c == e);

    a = vec2Make(-2.f, -2.f);
    c = vec2Len(a);
    ck_assert(c == e);

    a = vec2Make(2.f, -2.f);
    c = vec2Len(a);
    ck_assert(c == e);

    a = vec2Make(-2.f, 2.f);
    c = vec2Len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec2Norm)
{
    vec2 a = vec2Make(2.f, 2.f);
    vec2 e = vec2Make(1.f/sqrtf(2.f), 1.f/sqrtf(2.f));
    vec2 c = vec2Norm(a);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-2.f, -2.f);
    e = vec2Make(-1.f/sqrtf(2.f), -1.f/sqrtf(2.f));
    c = vec2Norm(a);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(2.f, -2.f);
    e = vec2Make(1.f/sqrtf(2.f), -1.f/sqrtf(2.f));
    c = vec2Norm(a);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-2.f, 2.f);
    e = vec2Make(-1.f/sqrtf(2.f), 1.f/sqrtf(2.f));
    c = vec2Norm(a);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2Min)
{
    vec2 a = vec2Make(3.f, 6.f);
    vec2 b = vec2Make(2.f, 8.f);
    vec2 e = vec2Make(2.f, 6.f);
    vec2 c = vec2Min(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-3.f, 6.f);
    b = vec2Make(2.f, 8.f);
    e = vec2Make(-3.f, 6.f);
    c = vec2Min(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(3.f, -6.f);
    b = vec2Make(2.f, 8.f);
    e = vec2Make(2.f, -6.f);
    c = vec2Min(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(3.f, -6.f);
    b = vec2Make(2.f, -8.f);
    e = vec2Make(2.f, -8.f);
    c = vec2Min(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

START_TEST(test_vec2Max)
{
    vec2 a = vec2Make(3.f, 6.f);
    vec2 b = vec2Make(2.f, 8.f);
    vec2 e = vec2Make(3.f, 8.f);
    vec2 c = vec2Max(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(-3.f, 6.f);
    b = vec2Make(2.f, 8.f);
    e = vec2Make(2.f, 8.f);
    c = vec2Max(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(2.f, -6.f);
    b = vec2Make(4.f, 8.f);
    e = vec2Make(4.f, 8.f);
    c = vec2Max(a, b);
    ck_assert_vec2_eq(c, e);

    a = vec2Make(3.f, -6.f);
    b = vec2Make(2.f, -8.f);
    e = vec2Make(3.f, -6.f);
    c = vec2Max(a, b);
    ck_assert_vec2_eq(c, e);
}
END_TEST

/*
 * Vec2 Testing suite.
 */
Suite *vec2Suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access;

    s = suite_create("ike/vec2");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec2_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec2Add);
    tcase_add_test(tc_arithm, test_vec2Sub);
    tcase_add_test(tc_arithm, test_vec2Scale);
    tcase_add_test(tc_arithm, test_vec2MulInner);
    tcase_add_test(tc_arithm, test_vec2SqrLen);
    tcase_add_test(tc_arithm, test_vec2Len);
    tcase_add_test(tc_arithm, test_vec2Norm);
    tcase_add_test(tc_arithm, test_vec2Min);
    tcase_add_test(tc_arithm, test_vec2Max);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec2Suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
