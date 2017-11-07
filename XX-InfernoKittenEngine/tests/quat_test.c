#include <stdlib.h>
#include <check.h>
#include <ike/quat.h>
#include <ike/vec3.h>
#include <ike/mathutil.h>
#include "quat_helper.h"
#include "mat4_helper.h"

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
    ck_assert_msg(quatIsAprox(c, e), "Wrong sum of quaternions");
}
END_TEST

START_TEST(test_quatMul)
{
    quat a = quatMake(1, 2, 3, 4);
    quat b = quatMake(1, 2, 3, 4);
    quat e = quatMake(-28, 4, 6, 8);
    quat c = quatMul(a, b);
    ck_assert_msg(quatIsAprox(c, e), "Wrong mul of quaternions");
}
END_TEST

START_TEST(test_quatScale)
{
    quat a = quatMake(1, 2, 3, 4);
    quat e = quatMake(3, 6, 9, 12);
    quat c = quatScale(a, 3);
    ck_assert_msg(quatIsAprox(c, e), "Wrong scale of quaternion");
}
END_TEST

START_TEST(test_quatNorm)
{
    quat a = quatMake(1, 2, 3, 4);
    quat e = quatMake(0.182574f, 0.365148f, 0.547723f, 0.730297f);
    quat c = quatNorm(a);
    ck_assert_msg(quatIsAprox(c, e), "Wrong norm of quaternion");
}
END_TEST

START_TEST(test_quatConjugate)
{
    quat a = quatMake(1, 2, 3, 4);
    quat e = quatMake(1, -2, -3, -4);
    quat c = quatConjugate(a);
    ck_assert_msg(quatIsAprox(c, e), "Wrong conjugate of quaternion");
}
END_TEST

START_TEST(test_quatDot)
{
    quat a = quatMake(1, 2, 3, 4);
    quat b = quatMake(1, 2, 3, 4);
    float e = 30.f;
    float c = quatDot(a, b);
    ck_assert_msg(fabs(e - c) < 0.001f, "Wrong dot product of quaternions");
}
END_TEST

START_TEST(test_quatInverse)
{
    quat a = quatMake(1, 2, 3, 4);
    quat e = quatMake(0.033333, -0.066667, -0.100000, -0.133333);
    quat c = quatInverse(a);
    ck_assert_msg(quatIsAprox(c, e), "Wrong inverse of quaternion");
}
END_TEST

START_TEST(test_quatLen)
{
    quat a = quatMake(1, 2, 3, 4);
    float e = 5.47723f;
    float c = quatLen(a);
    ck_assert_msg(fabs(e - c) < 0.001f, "Wrong length of quaternion");
}
END_TEST

START_TEST(test_quatAxisAngle)
{
    quat e = quatMake(0.707107, 0.707107, 0, 0);
    quat a = quatAxisAngle(vec3Make(1, 0, 0), TORAD(90.f));
    ck_assert_msg(quatIsAprox(a, e), "Wrong quaternion from axis(1,0,0) angle");

    e = quatMake(0.707107, 0, 0.707107, 0);
    a = quatAxisAngle(vec3Make(0, 1, 0), TORAD(90.f));
    ck_assert_msg(quatIsAprox(a, e), "Wrong quaternion from axis(0,1,0) angle");

    e = quatMake(0.707107, 0, 0, 0.707107);
    a = quatAxisAngle(vec3Make(0, 0, 1), TORAD(90.f));
    ck_assert_msg(quatIsAprox(a, e), "Wrong quaternion from axis(0,0,1) angle");
}
END_TEST

START_TEST(test_quatToMat4)
{
    quat a = quatMake(1, 2, 3, 4);
    mat4 e = {
        -0.666667f,  0.666667f, 0.333333f, 0.000000f,
         0.133333f, -0.333333f, 0.933333f, 0.000000f,
         0.733333f,  0.666667f, 0.133333f, 0.000000f,
         0.000000f,  0.000000f, 0.000000f, 1.000000f
    };

    mat4 b = quatToMat4(a);
    ck_assert_msg(mat4IsAprox(b, e), "Wrong matrix(4) from quaternion");
}
END_TEST

START_TEST(test_quatMakeEuler)
{
    quat e = quatMake(0.706434f, 0.560986f, 0.430459f, 0.030844f);
    quat a = quatMakeEuler(vec3Make(TORAD(90), TORAD(35), TORAD(40)));
    ck_assert_msg(quatIsAprox(a, e), "Wrong quaternion from euler angles");
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
    tcase_add_test(tc_arithm, test_quatMul);
    tcase_add_test(tc_arithm, test_quatNorm);
    tcase_add_test(tc_arithm, test_quatConjugate);
    tcase_add_test(tc_arithm, test_quatDot);
    tcase_add_test(tc_arithm, test_quatInverse);
    tcase_add_test(tc_arithm, test_quatLen);
    tcase_add_test(tc_arithm, test_quatAxisAngle);
    tcase_add_test(tc_arithm, test_quatToMat4);
    tcase_add_test(tc_arithm, test_quatMakeEuler);
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

