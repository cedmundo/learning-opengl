#include <stdlib.h>
#include <check.h>
#include <ike/vec3.h>
#include "vec3_helper.h"

START_TEST(test_vec3_access)
{
    vec3 a = vec3Make(.5f, 5.f, -5.f);

    ck_assert_msg(a.x == .5f, "X Member of vector should be as same as asigned on vec3Make");
    ck_assert_msg(a.y == 5.f, "Y Member of vector should be as same as asigned on vec3Make");
    ck_assert_msg(a.z == -5.f, "Z Member of vector should be as same as asigned on vec3Make");
    ck_assert_msg(a.xyz[0] == .5f, "Array member 0 of vector should be as same as asigned on vec3Make");
    ck_assert_msg(a.xyz[1] == 5.f, "Array member 1 of vector should be as same as asigned on vec3Make");
    ck_assert_msg(a.xyz[2] == -5.f, "Array member 2 of vector should be as same as asigned on vec3Make");
}
END_TEST

START_TEST(test_vec3Add)
{
    vec3 a = vec3Make(.5f, 5.f, -5.f);
    vec3 b = vec3Make(.5f, 5.f, -5.f);
    vec3 e = vec3Make(1.f, 10.f, -10.f);
    vec3 c = vec3Add(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-.5f, -5.f, 5.f);
    b = vec3Make(.5f, 5.f, -5.f);
    e = vec3Make(0.f, 0.f, 0.f);
    c = vec3Add(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Sub)
{
    vec3 a = vec3Make(.5f, 5.f, -5.f);
    vec3 b = vec3Make(.5f, 5.f, -5.f);
    vec3 e = vec3Make(0.f, 0.f, 0.f);
    vec3 c = vec3Sub(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(6.f, 4.f, 5.f);
    b = vec3Make(5.f, 2.f, 2.f);
    e = vec3Make(1.f, 2.f, 3.f);
    c = vec3Sub(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-.5f, 5.f, 5.f);
    b = vec3Make(.5f, 2.f, -5.f);
    e = vec3Make(-1.f, 3.f, 10.f);
    c = vec3Sub(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Scale)
{
    vec3 a = vec3Make(.5f, 5.f, -5.f);
    float b = 3.f;
    vec3 e = vec3Make(1.5f, 15.f, -15.f);
    vec3 c = vec3Scale(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(6.f, 4.f, 5.f);
    b = 3.f;
    e = vec3Make(18.f, 12.f, 15.f);
    c = vec3Scale(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-.5f, 5.f, -5.f);
    b = -2.f;
    e = vec3Make(1.f, -10.f, 10.f);
    c = vec3Scale(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3MulInner)
{
    vec3 a = vec3Make(2.f, 10.f, 3.f);
    vec3 b = vec3Make(3.f, 2.f, 5.f);
    float e = 41.f;
    float c = vec3MulInner(a, b);
    ck_assert(c == e);

    a = vec3Make(-2.f, 10.f, .3f);
    b = vec3Make(3.f, 2.f, 2.f);
    e = 14.6f;
    c = vec3MulInner(a, b);
    ck_assert(c == e);

    a = vec3Make(2.f, -10.f, 0.f);
    b = vec3Make(3.f, 2.f, 10.f);
    e = -14.f;
    c = vec3MulInner(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3SqrLen)
{
    float e = 12.f;

    vec3 a = vec3Make(2.f, 2.f, 2.f);
    float c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, -2.f, 2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(2.f, -2.f, 2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, 2.f, 2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, -2.f, -2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(2.f, -2.f, -2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, 2.f, -2.f);
    c = vec3SqrLen(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3Len)
{
    float e = sqrtf(12.f);

    vec3 a = vec3Make(2.f, 2.f, 2.f);
    float c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, -2.f, 2.f);
    c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(2.f, -2.f, 2.f);
    c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, 2.f, 2.f);
    c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, -2.f, -2.f);
    c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(2.f, -2.f, -2.f);
    c = vec3Len(a);
    ck_assert(c == e);

    a = vec3Make(-2.f, 2.f, -2.f);
    c = vec3Len(a);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3Norm)
{
    vec3 a = vec3Make(2.f, 2.f, 2.f);
    vec3 e = vec3Make(1.f/sqrtf(3.f), 1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    vec3 c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-2.f, -2.f, 2.f);
    e = vec3Make(-1.f/sqrtf(3.f), -1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(2.f, -2.f, 2.f);
    e = vec3Make(1.f/sqrtf(3.f), -1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-2.f, 2.f, 2.f);
    e = vec3Make(-1.f/sqrtf(3.f), 1.f/sqrtf(3.f), 1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-2.f, -2.f, -2.f);
    e = vec3Make(-1.f/sqrtf(3.f), -1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(2.f, -2.f, -2.f);
    e = vec3Make(1.f/sqrtf(3.f), -1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-2.f, 2.f, -2.f);
    e = vec3Make(-1.f/sqrtf(3.f), 1.f/sqrtf(3.f), -1.f/sqrtf(3.f));
    c = vec3Norm(a);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Min)
{
    vec3 a = vec3Make(3.f, 6.f, 4.f);
    vec3 b = vec3Make(2.f, 8.f, 2.f);
    vec3 e = vec3Make(2.f, 6.f, 2.f);
    vec3 c = vec3Min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-3.f, 6.f, -1.f);
    b = vec3Make(2.f, 8.f, -1.f);
    e = vec3Make(-3.f, 6.f, -1.f);
    c = vec3Min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(3.f, -6.f, 3.f);
    b = vec3Make(2.f, 8.f, -3.f);
    e = vec3Make(2.f, -6.f,-3.f);
    c = vec3Min(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(3.f, -6.f,-2.f);
    b = vec3Make(2.f, -8.f, 2.f);
    e = vec3Make(2.f, -8.f,-2.f);
    c = vec3Min(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Max)
{
    vec3 a = vec3Make(3.f, 6.f, 5.f);
    vec3 b = vec3Make(2.f, 8.f, 7.f);
    vec3 e = vec3Make(3.f, 8.f, 7.f);
    vec3 c = vec3Max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-3.f, 6.f, 3.f);
    b = vec3Make(2.f, 8.f, -3.f);
    e = vec3Make(2.f, 8.f, 3.f);
    c = vec3Max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(2.f, -6.f, 1.f);
    b = vec3Make(4.f, 8.f, 1.f);
    e = vec3Make(4.f, 8.f, 1.f);
    c = vec3Max(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(3.f, -6.f, -3.f);
    b = vec3Make(2.f, -8.f, -2.f);
    e = vec3Make(3.f, -6.f, -2.f);
    c = vec3Max(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Dot)
{
    vec3 a = vec3Make(1.f, 2.f, 3.f);
    vec3 b = vec3Make(4.f, 5.f, 6.f);
    float e = 32.f;
    float c = vec3Dot(a, b);
    ck_assert(c == e);

    a = vec3Make(1.f, -2.f, 3.f);
    b = vec3Make(-4.f, 5.f, -6.f);
    e = -32.f;
    c = vec3Dot(a, b);
    ck_assert(c == e);
}
END_TEST

START_TEST(test_vec3Cross)
{
    vec3 a = vec3Make(1.f, 2.f, 3.f);
    vec3 b = vec3Make(4.f, 5.f, 6.f);
    vec3 e = vec3Make(-3.f, 6.f, -3.f);
    vec3 c = vec3Cross(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-1.f, 2.f, -3.f);
    b = vec3Make(4.f, -5.f, 6.f);
    e = vec3Make(-3.f, -6.f, -3.f);
    c = vec3Cross(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

START_TEST(test_vec3Reflect)
{
    vec3 a = vec3Make(1.f, 2.f, 3.f);
    vec3 b = vec3Make(4.f, 5.f, 6.f);
    vec3 e = vec3Make(-2.32468f, -2.15584f, -1.98701f);
    vec3 c = vec3Reflect(a, b);
    ck_assert_vec3_eq(c, e);

    a = vec3Make(-2.f, 3.f, -6.f);
    b = vec3Make(1.f, -4.f, 5.f);
    e = vec3Make(0.0952381f, -5.38095f, 4.47619f);
    c = vec3Reflect(a, b);
    ck_assert_vec3_eq(c, e);
}
END_TEST

/*
 * Vec3 Testing suite.
 */
Suite *vec3Suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_make;

    s = suite_create("ike/vec3");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_vec3_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_vec3Add);
    tcase_add_test(tc_arithm, test_vec3Sub);
    tcase_add_test(tc_arithm, test_vec3Scale);
    tcase_add_test(tc_arithm, test_vec3MulInner);
    tcase_add_test(tc_arithm, test_vec3SqrLen);
    tcase_add_test(tc_arithm, test_vec3Len);
    tcase_add_test(tc_arithm, test_vec3Norm);
    tcase_add_test(tc_arithm, test_vec3Min);
    tcase_add_test(tc_arithm, test_vec3Max);
    tcase_add_test(tc_arithm, test_vec3Dot);
    tcase_add_test(tc_arithm, test_vec3Cross);
    tcase_add_test(tc_arithm, test_vec3Reflect);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = vec3Suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

