#include <stdlib.h>
#include <check.h>
#include <ike/quat.h>
#include "quat_helper.h"

START_TEST(test_quat_access)
{
    quat a = quatMake(.5f, 5.f, -5.f, -.5f);

    ck_assert_msg(a.w == .5f, "W Member of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.x == 5.f, "X Member of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.y == -5.f, "Y Member of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.z == -.5f, "Z Member of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.wxyz[0] == .5f, "Array member 0 of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.wxyz[1] == 5.f, "Array member 1 of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.wxyz[2] == -5.f, "Array member 2 of vector should be as same as asigned on quatMake");
    ck_assert_msg(a.wxyz[3] == -.5f, "Array member 3 of vector should be as same as asigned on quatMake");
}
END_TEST

START_TEST(test_quatAdd)
{
    quat a = quatMake(.5f, 5.f, -5.f, -.5f);
    quat b = quatMake(.5f, 5.f, -5.f, -.5f);
    quat e = quatMake(1.f, 10.f, -10.f, -1.f);
    quat c = quatAdd(a, b);
    ck_assert_quat_eq(c, e);
}
END_TEST

START_TEST(test_quatMul)
{
    quat a = quatMake(1, 2, 3, 4);
    quat b = quatMake(4, 3, 2, 1.);
    quat e = quatMake(6, 24, 12, -12);
    quat c = quatMul(a, b);
    ck_assert_quat_eq(c, e);
}
END_TEST

Suite *quatSuite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_make;

    s = suite_create("ike/quat");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_quat_access);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_quatAdd);
    suite_add_tcase(s, tc_arithm);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = quatSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

