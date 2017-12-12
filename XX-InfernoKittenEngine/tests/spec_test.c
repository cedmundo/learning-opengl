#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <tests/config.h>
#include <ike/spec.h>

START_TEST(test_initDestroy)
{
}
END_TEST

Suite *specSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/spec");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_initDestroy);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = specSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

