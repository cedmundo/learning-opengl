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
}
END_TEST

/*
 * Vec2 Testing suite.
 */
Suite *vec2_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/vec2");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_vec2_access);
    tcase_add_test(tc_core, test_vec2_add);
    tcase_add_test(tc_core, test_vec2_sub);
    suite_add_tcase(s, tc_core);

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
