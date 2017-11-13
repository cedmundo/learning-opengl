#include <stdlib.h>
#include <check.h>
#include <ike/mathutil.h>

START_TEST(test_mathutil_round)
{
    float a = 1.123456789f;
    float e = 1.1235f;
    float b = ROUND4(a);
    ck_assert(b == e);

    a = 1.1234f;
    e = 1.1234f;
    b = ROUND4(a);
    ck_assert(b == e);
}
END_TEST

START_TEST(test_mathutil_max)
{
    int a = 3;
    int b = 2;
    int e = 3;
    int c = MAX(int, a, b);
    ck_assert(c == e);

    float af = 3.4f;
    float bf = 3.2f;
    float ef = 3.4f;
    float cf = MAX(float, af, bf);
    ck_assert(cf == ef);
}
END_TEST

START_TEST(test_mathutil_min)
{
    int a = 3;
    int b = 2;
    int e = 2;
    int c = MIN(int, a, b);
    ck_assert(c == e);

    float af = 3.4f;
    float bf = 3.2f;
    float ef = 3.2f;
    float cf = MIN(float, af, bf);
    ck_assert(cf == ef);
}
END_TEST


START_TEST(test_mathutil_convertions)
{
    float a = 90.f;
    float e = ROUND4(1.570797f);
    float b = ROUND4(TORAD(a));
    ck_assert_msg(b == e, "Failed degrees to radians convertion");

    a = 1.2f;
    e = ROUND4(68.75496f);
    b = ROUND4(TODEG(a));
    ck_assert_msg(b == e, "Failed radians to degrees convertion");
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/mathutil");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_mathutil_round);
    tcase_add_test(tc_core, test_mathutil_convertions);
    tcase_add_test(tc_core, test_mathutil_max);
    tcase_add_test(tc_core, test_mathutil_min);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = mat4Suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

