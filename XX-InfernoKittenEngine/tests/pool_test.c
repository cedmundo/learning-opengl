#include <stdlib.h>
#include <check.h>
#include <ike/pool.h>

START_TEST(test_initRelease)
{
    ikePool pool;
    ikePoolInit(&pool, IKE_POOL_SMALL);

    size_t a = ikePoolAvailable(&pool);
    size_t e = IKE_POOL_SMALL;
    ck_assert_msg(a == e, "bad memory allocation for pool");

    ikePoolDestroy(&pool);
    a = ikePoolAvailable(&pool);
    e = (size_t) 0L;
    ck_assert_msg(a == e, "memory marked as avilable after destroying pool");
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/pool");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_initRelease);
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

