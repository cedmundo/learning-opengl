#include <stdlib.h>
#include <check.h>
#include <ike/vec3.h>
#include <ike/mat4.h>
#include <ike/mathutil.h>
#include "mat4_helper.h"
#include "vec4_helper.h"

START_TEST(test_mat4_access)
{
    mat4 a = mat4_identity;
    ck_assert_msg(a.xx == 1, "XX Should be 1 (identity)");
    ck_assert_msg(a.yy == 1, "YY Should be 1 (identity)");
    ck_assert_msg(a.zz == 1, "ZZ Should be 1 (identity)");
    ck_assert_msg(a.ww == 1, "WW Should be 1 (identity)");

    ck_assert_msg(a.xy == 0, "XY Should be 0 (identity)");
    ck_assert_msg(a.yz == 0, "YZ Should be 0 (identity)");
    ck_assert_msg(a.zw == 0, "ZW Should be 0 (identity)");
    ck_assert_msg(a.wx == 0, "WX Should be 0 (identity)");

    float *adata = a.raw;
    ck_assert_msg(adata[0]  == 1, "Array index 0 should be 1 (identity)");
    ck_assert_msg(adata[5]  == 1, "Array index 5 should be 1 (identity)");
    ck_assert_msg(adata[10] == 1, "Array index 10 should be 1 (identity)");
    ck_assert_msg(adata[15] == 1, "Array index 15 should be 1 (identity)");

    ck_assert_msg(adata[1]  == 0, "Array index 1 should be 0 (identity)");
    ck_assert_msg(adata[6]  == 0, "Array index 6 should be 0 (identity)");
    ck_assert_msg(adata[11] == 0, "Array index 11 should be 0 (identity)");
    ck_assert_msg(adata[12] == 0, "Array index 12 should be 0 (identity)");
}
END_TEST

START_TEST(test_mat4_column_major)
{
    mat4 a = mat4_zero;
    a.xx = 1;
    a.xy = 1;
    a.xz = 1;
    a.xw = 1;

    a.zx = 1;
    a.zy = 1;
    a.zz = 1;
    a.zw = 1;

    float *adata = a.raw;
    ck_assert_msg(adata[0] == 1, "Array index 0 should be 1");
    ck_assert_msg(adata[1] == 1, "Array index 1 should be 1");
    ck_assert_msg(adata[2] == 1, "Array index 2 should be 1");
    ck_assert_msg(adata[3] == 1, "Array index 3 should be 1");

    ck_assert_msg(adata[4] == 0, "Array index 4 should be 0");
    ck_assert_msg(adata[5] == 0, "Array index 5 should be 0");
    ck_assert_msg(adata[6] == 0, "Array index 6 should be 0");
    ck_assert_msg(adata[7] == 0, "Array index 7 should be 0");

    ck_assert_msg(adata[8]  == 1, "Array index 8 should be 1");
    ck_assert_msg(adata[9]  == 1, "Array index 9 should be 1");
    ck_assert_msg(adata[10] == 1, "Array index 10 should be 1");
    ck_assert_msg(adata[11] == 1, "Array index 11 should be 1");

    ck_assert_msg(adata[12] == 0, "Array index 12 should be 0");
    ck_assert_msg(adata[13] == 0, "Array index 13 should be 0");
    ck_assert_msg(adata[14] == 0, "Array index 14 should be 0");
    ck_assert_msg(adata[15] == 0, "Array index 15 should be 0");
}
END_TEST

START_TEST(test_mat4_get_column)
{
     mat4 a = {
         1,  5,  9, 13,
         2,  6, 10, 14,
         3,  7, 11, 15,
         4,  8, 12, 16
    };
    vec4 b = mat4_col(a, 0);
    vec4 e = vec4_make(1, 2, 3, 4);
    ck_assert_vec4_eq(b, e);

    b = mat4_col(a, 1);
    e = vec4_make(5, 6, 7, 8);
    ck_assert_vec4_eq(b, e);

    b = mat4_col(a, 2);
    e = vec4_make(9, 10, 11, 12);
    ck_assert_vec4_eq(b, e);

    b = mat4_col(a, 3);
    e = vec4_make(13, 14, 15, 16);
    ck_assert_vec4_eq(b, e);
}
END_TEST

START_TEST(test_mat4_get_row)
{
    mat4 a = {
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };
    vec4 b = mat4_row(a, 0);
    vec4 e = vec4_make(1, 2, 3, 4);
    ck_assert_vec4_eq(b, e);

    b = mat4_row(a, 1);
    e = vec4_make(5, 6, 7, 8);
    ck_assert_vec4_eq(b, e);

    b = mat4_row(a, 2);
    e = vec4_make(9, 10, 11, 12);
    ck_assert_vec4_eq(b, e);

    b = mat4_row(a, 3);
    e = vec4_make(13, 14, 15, 16);
    ck_assert_vec4_eq(b, e);
}
END_TEST

START_TEST(test_mat4_transpose)
{
    mat4 a = {
         1,  5,  9, 13,
         2,  6, 10, 14,
         3,  7, 11, 15,
         4,  8, 12, 16
    };
    mat4 e = {
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };

    mat4 b = mat4_transpose(a);
    ck_assert_msg(mat4_is_aprox(b, e) == 1, "Transpose is not equal");
}
END_TEST

START_TEST(test_mat4_add)
{
    mat4 a = {
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4
    };

    mat4 b = {
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1
    };

    mat4 e = {
        5, 5, 5, 5,
        5, 5, 5, 5,
        5, 5, 5, 5,
        5, 5, 5, 5
    };

    mat4 c = mat4_add(a, b);
    ck_assert_msg(mat4_is_aprox(c, e) == 1, "Wrong matrix addition");
}
END_TEST

START_TEST(test_mat4_sub)
{
    mat4 a = {
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4
    };

    mat4 b = {
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1
    };

    mat4 e = {
        -3, -1, 1, 3,
        -3, -1, 1, 3,
        -3, -1, 1, 3,
        -3, -1, 1, 3
    };

    mat4 c = mat4_sub(a, b);
    ck_assert_msg(mat4_is_aprox(c, e) == 1, "Wrong matrix substraction");
}
END_TEST

START_TEST(test_mat4_scale)
{
    mat4 a = {
        1,  2, 3, 4,
        1, -2, 3, 4,
        1,  2, 3, 4,
        1, -2, 3, 4
    };

    float b = 2.f;

    mat4 e = {
        2,  4, 6, 8,
        2, -4, 6, 8,
        2,  4, 6, 8,
        2, -4, 6, 8
    };

    mat4 c = mat4_scale(a, b);
    ck_assert_msg(mat4_is_aprox(c, e) == 1, "Wrong matrix scale");
}
END_TEST

START_TEST(test_mat4_mul)
{
    mat4 a = {
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
    };

    mat4 b = {
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1,
        4, 3, 2, 1,
    };

    mat4 e = {
        40, 30, 20, 10,
        40, 30, 20, 10,
        40, 30, 20, 10,
        40, 30, 20, 10
    };

    mat4 c = mat4_mul(a, b);
    ck_assert_msg(mat4_is_aprox(c, e) == 1, "Wrong matrix multiplication");
}
END_TEST

START_TEST(test_mat4_mul_vec4)
{
    mat4 a = {
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4
    };

    vec4 b = vec4_make(1, 2, 3, 4);
    vec4 e = vec4_make(30, 30, 30, 30);
    vec4 c = mat4_mul_vec4(a, b);
    ck_assert_vec4_eq(c, e);
}
END_TEST

START_TEST(test_mat4_make_scale)
{
    vec3 a = vec3_make(1.5f, 1.5f, 1.5f);
    mat4 e = {
        1.5f, 0, 0, 0,
        0, 1.5f, 0, 0,
        0, 0, 1.5f, 0,
        0, 0, 0, 1.f,
    };

    mat4 b = mat4_make_scale(a);
    ck_assert_msg(mat4_is_aprox(b, e) == 1, "Wrong scale model matrix");
}
END_TEST

START_TEST(test_mat4_make_rotation)
{
    vec3 a = vec3_make(1.f, 0.f, 2.f);
    float b = TORAD(90.0f);
    mat4 e = {
         0.200000f,  0.894427f, 0.400000f,  0.000000f,
        -0.894427f, -0.000000f, 0.447214f,  0.000000f,
         0.400000f, -0.447214f, 0.800000f,  0.000000f,
         0.000000f,  0.000000f, 0.000000f,  1.000000f
    };

    mat4 c = mat4_make_rotation(a, b);
    ck_assert_msg(mat4_is_aprox(c, e) == 1, "Wrong rotation model matrix");
}
END_TEST

START_TEST(test_mat4_make_rotation_x)
{
    float a = 35.f;
    mat4 e = {
         1.000000f,  0.000000f, 0.000000f, 0.000000f,
        -0.000000f,  0.819152f, 0.573576f, 0.000000f,
         0.000000f, -0.573576f, 0.819152f, 0.000000f,
         0.000000f,  0.000000f, 0.000000f, 1.000000f
    };

    mat4 b = mat4_make_rotation_x(TORAD(a));
    ck_assert_msg(mat4_is_aprox(b, e) == 1, "Wrong rotation by X model matrix");
}
END_TEST

START_TEST(test_mat4_make_rotation_y)
{
    float a = 35.f;
    mat4 e = {
         0.819152f,  0.000000f, -0.573576f, 0.000000f,
        -0.000000f,  1.000000f,  0.000000f, 0.000000f,
         0.573576f, -0.000000f,  0.819152f, 0.000000f,
         0.000000f,  0.000000f,  0.000000f, 1.000000f
    };

    mat4 b = mat4_make_rotation_y(TORAD(a));
    ck_assert_msg(mat4_is_aprox(b, e) == 1, "Wrong rotation by Y model matrix");
}
END_TEST

START_TEST(test_mat4_make_rotation_z)
{
    float a = 35.f;
    mat4 e = {
         0.819152f,  0.573576f, 0.000000f, 0.000000f,
        -0.573576f,  0.819152f, 0.000000f, 0.000000f,
         0.000000f, -0.000000f, 1.000000f, 0.000000f,
         0.000000f,  0.000000f, 0.000000f, 1.000000f
    };

    mat4 b = mat4_make_rotation_z(TORAD(a));
    ck_assert_msg(mat4_is_aprox(b, e) == 1, "Wrong rotation by Z model matrix");
}
END_TEST

START_TEST(test_mat4_make_ortho)
{
    mat4 e = {
         0.020000f,  0.000000f,  0.000000f, 0.000000f,
         0.000000f, -0.020000f,  0.000000f, 0.000000f,
         0.000000f,  0.000000f, -0.020020f, 0.000000f,
        -1.000000f,  1.000000f, -1.002002f, 1.000000f
    };

    mat4 a = mat4_make_ortho(0.f, 100.f, 100.f, 0.f, 0.1f, 100.f);
    ck_assert_msg(mat4_is_aprox(a, e) == 1, "Wrong ortho projection matrix");
}
END_TEST

START_TEST(test_mat4_make_perspective)
{
    mat4 e = {
        -0.224922f,  0.000000f,  0.000000f,  0.000000f,
         0.000000f, -0.224922f,  0.000000f,  0.000000f,
         0.000000f,  0.000000f, -1.002002f, -1.000000f,
         0.000000f,  0.000000f, -0.200200f,  0.000000f
    };

    mat4 a = mat4_make_perspective(35.f, 1.f, 0.1f, 100.f);
    ck_assert_msg(mat4_is_aprox(a, e) == 1, "Wrong perspective projection matrix");
}
END_TEST

START_TEST(test_mat4_look_at)
{
    mat4 e = {
         0.707107f, -0.408248f,  0.577350f, 0.000000f,
         0.000000f,  0.816497f,  0.577350f, 0.000000f,
        -0.707107f, -0.408248f,  0.577350f, 0.000000f,
        -0.000000f, -0.000000f, -1.732051f, 1.000000f
    };

    vec3 eye = {0.f, 0.f, 0.f};
    vec3 center = {0.f, 0.f, 0.f};
    mat4 a = mat4_look_at(eye, center, vec3_up);
    ck_assert_msg(mat4_is_aprox(a, e) == 1, "Wrong look at matrix");
}
END_TEST

Suite *mat4_suite(void)
{
    Suite *s;
    TCase *tc_arithm, *tc_access, *tc_model, *tc_proj, *tc_misc;

    s = suite_create("ike/mat4");

    tc_access = tcase_create("access");
    tcase_add_test(tc_access, test_mat4_access);
    tcase_add_test(tc_access, test_mat4_column_major);
    tcase_add_test(tc_access, test_mat4_get_column);
    tcase_add_test(tc_access, test_mat4_get_row);
    suite_add_tcase(s, tc_access);

    tc_arithm = tcase_create("arithmetic");
    tcase_add_test(tc_arithm, test_mat4_transpose);
    tcase_add_test(tc_arithm, test_mat4_add);
    tcase_add_test(tc_arithm, test_mat4_sub);
    tcase_add_test(tc_arithm, test_mat4_scale);
    tcase_add_test(tc_arithm, test_mat4_mul);
    tcase_add_test(tc_arithm, test_mat4_mul_vec4);
    suite_add_tcase(s, tc_arithm);

    tc_model = tcase_create("model");
    tcase_add_test(tc_model, test_mat4_make_scale);
    tcase_add_test(tc_model, test_mat4_make_rotation);
    tcase_add_test(tc_model, test_mat4_make_rotation_x);
    tcase_add_test(tc_model, test_mat4_make_rotation_y);
    tcase_add_test(tc_model, test_mat4_make_rotation_z);
    suite_add_tcase(s, tc_model);

    tc_proj = tcase_create("projection");
    tcase_add_test(tc_proj, test_mat4_make_ortho);
    tcase_add_test(tc_proj, test_mat4_make_perspective);
    suite_add_tcase(s, tc_proj);

    tc_misc = tcase_create("misc");
    tcase_add_test(tc_misc, test_mat4_look_at);
    suite_add_tcase(s, tc_misc);

    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = mat4_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
