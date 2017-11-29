#include <stdlib.h>
#include <check.h>
#include <ike/vec4.h>
#include "vec4_helper.h"

START_TEST(test_vec4_access)
{
    vec4 a = vec4Make(.5f, 5.f, -5.f, -.5f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.z == -5.f, "Z Member of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.w == -.5f, "W Member of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.xyzw[0] == .5f, "Array member 0 of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.xyzw[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.xyzw[2] == -5.f, "Array member 2 of vector should be as same as asigned on vec4Make");
    ck_assert_msg(a.xyzw[3] == -.5f, "Array member 3 of vector should be as same as asigned on vec4Make");
}
END_TEST

START_TEST(test_vec4Add)
{
    vec4 a = vec4Make(.5f, 5.f, -5.f, -.5f);
    vec4 b = vec4Make(.5f, 5.f, -5.f, -.5f);
    vec4 e = vec4Make(1.f, 10.f, -10.f, -1.f);
    vec4 c = vec4Add(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-.5f, -5.f, 5.f, -.5f);
    b = vec4Make(.5f, 5.f, -5.f, -.5f);
    e = vec4Make(0.f, 0.f, 0.f, -1.f);
    c = vec4Add(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4Sub)
{
    vec4 a = vec4Make(.5f, 5.f, -5.f, -.5f);
    vec4 b = vec4Make(.5f, 5.f, -5.f, -.5f);
    vec4 e = vec4Make(0.f, 0.f, 0.f, 0.f);
    vec4 c = vec4Sub(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(6.f, 4.f, 5.f, 8.f);
    b = vec4Make(5.f, 2.f, 2.f, 2.f);
    e = vec4Make(1.f, 2.f, 3.f, 6.f);
    c = vec4Sub(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-.5f, 5.f, 5.f, -.5f);
    b = vec4Make(.5f, 2.f, -5.f, 3.f);
    e = vec4Make(-1.f, 3.f, 10.f, -3.5f);
    c = vec4Sub(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4Scale)
{
    vec4 a = vec4Make(.5f, 5.f, -5.f, -.5f);
    float b = 3.f;
    vec4 e = vec4Make(1.5f, 15.f, -15.f, -1.5f);
    vec4 c = vec4Scale(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(6.f, 4.f, 5.f, 1.f);
    b = 3.f;
    e = vec4Make(18.f, 12.f, 15.f, 3.f);
    c = vec4Scale(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-.5f, 5.f, -5.f, -.5f);
    b = -2.f;
    e = vec4Make(1.f, -10.f, 10.f, 1.f);
    c = vec4Scale(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4MulInner)
{
    vec4 a = vec4Make(2.f, 10.f, 3.f, 2.f);
    vec4 b = vec4Make(3.f, 2.f, 5.f, 1.f);
    float e = 43.f;
    float c = vec4MulInner(a, b);
    ck_assert(c == e);

    a = vec4Make(-2.f, 10.f, .3f, 3.f);
    b = vec4Make(3.f, 2.f, 2.f, 2.f);
    e = 20.6f;
    c = vec4MulInner(a, b);
    ck_assert(c == e);

    a = vec4Make(2.f, -10.f, 0.f, -3.f);
    b = vec4Make(3.f, 2.f, 10.f, 5.f);
    e = -29.f;
    c = vec4MulInner(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4SqrLen)
{
    float e = 16.f;

    vec4 a = vec4Make(2.f, 2.f, 2.f, 2.f);
    float c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, 2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, 2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, 2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, -2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, -2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, -2.f, 2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, 2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, 2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, 2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, -2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, -2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, -2.f, -2.f);
    c = vec4SqrLen(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4Len)
{
    float e = sqrtf(16.f);

    vec4 a = vec4Make(2.f, 2.f, 2.f, 2.f);
    float c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, 2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, 2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, 2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, -2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, -2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, -2.f, 2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, 2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, 2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, 2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, -2.f, -2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(2.f, -2.f, -2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);

    a = vec4Make(-2.f, 2.f, -2.f, -2.f);
    c = vec4Len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec4Norm)
{
    vec4 a = vec4Make(2.f, 2.f, 2.f, 2.f);
    vec4 e = vec4Make(1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    vec4 c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, -2.f, 2.f, 2.f);
    e = vec4Make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, -2.f, 2.f, 2.f);
    e = vec4Make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, 2.f, 2.f, 2.f);
    e = vec4Make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, -2.f, -2.f, 2.f);
    e = vec4Make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, -2.f, -2.f, 2.f);
    e = vec4Make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, 2.f, -2.f, 2.f);
    e = vec4Make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, 2.f, 2.f, -2.f);
    e = vec4Make(1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, -2.f, 2.f, -2.f);
    e = vec4Make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, -2.f, 2.f, -2.f);
    e = vec4Make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, 2.f, 2.f, -2.f);
    e = vec4Make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, -2.f, -2.f, -2.f);
    e = vec4Make(-1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, -2.f, -2.f, -2.f);
    e = vec4Make(1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-2.f, 2.f, -2.f, -2.f);
    e = vec4Make(-1.f/sqrtf(4.f), 1.f/sqrtf(4.f), -1.f/sqrtf(4.f), -1.f/sqrtf(4.f));
    c = vec4Norm(a);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4Min)
{
    vec4 a = vec4Make(3.f, 6.f, 4.f, 1.f);
    vec4 b = vec4Make(2.f, 8.f, 2.f, 1.f);
    vec4 e = vec4Make(2.f, 6.f, 2.f, 1.f);
    vec4 c = vec4Min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-3.f, 6.f, -1.f, -2.f);
    b = vec4Make(2.f, 8.f, -1.f, -3.5f);
    e = vec4Make(-3.f, 6.f, -1.f, -3.5f);
    c = vec4Min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(3.f, -6.f, 3.f, 2.f);
    b = vec4Make(2.f, 8.f, -3.f, 2.f);
    e = vec4Make(2.f, -6.f,-3.f, 2.f);
    c = vec4Min(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(3.f, -6.f,-2.f, 1.f);
    b = vec4Make(2.f, -8.f, 2.f, 1.f);
    e = vec4Make(2.f, -8.f,-2.f, 1.f);
    c = vec4Min(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_vec4Max)
{
    vec4 a = vec4Make(3.f, 6.f, 5.f, 4.f);
    vec4 b = vec4Make(2.f, 8.f, 7.f, 4.f);
    vec4 e = vec4Make(3.f, 8.f, 7.f, 4.f);
    vec4 c = vec4Max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(-3.f, 6.f, 3.f, 1.f);
    b = vec4Make(2.f, 8.f, -3.f, 1.1f);
    e = vec4Make(2.f, 8.f, 3.f, 1.1f);
    c = vec4Max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(2.f, -6.f, 1.f, 3.f);
    b = vec4Make(4.f, 8.f, 1.f, 3.f);
    e = vec4Make(4.f, 8.f, 1.f, 3.f);
    c = vec4Max(a, b);
    ck_assert_vec4_eq(c, e);

    a = vec4Make(3.f, -6.f, -3.f, -2.f);
    b = vec4Make(2.f, -8.f, -2.f, -2.f);
    e = vec4Make(3.f, -6.f, -2.f, -2.f);
    c = vec4Max(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

Suite *vec4Suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_make;

    s = suite_create("ike/vec4");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec4_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec4Add);
    tcase_add_test(tc_arithm, test_vec4Sub);
    tcase_add_test(tc_arithm, test_vec4Scale);
    tcase_add_test(tc_arithm, test_vec4MulInner);
    tcase_add_test(tc_arithm, test_vec4SqrLen);
    tcase_add_test(tc_arithm, test_vec4Len);
    tcase_add_test(tc_arithm, test_vec4Norm);
    tcase_add_test(tc_arithm, test_vec4Min);
    tcase_add_test(tc_arithm, test_vec4Max);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec4Suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

