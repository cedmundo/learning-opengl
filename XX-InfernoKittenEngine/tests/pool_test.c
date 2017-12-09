#include <stdlib.h>
#include <check.h>
#include <ike/pool.h>

#define is_aligned(POINTER, BYTE_COUNT) \
    (((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)

#include <stdio.h>

START_TEST(test_initRelease)
{
    ikePool pool;
    ck_assert_msg(ikePoolInit(&pool, IKE_POOL_SMALL) == IKE_POOL_OK, "could not init pool");

    size_t a = ikePoolAvailable(&pool);
    size_t e = IKE_POOL_SMALL;
    ck_assert_msg(a == e, "bad memory allocation for pool");

    ikePoolDestroy(&pool);
    a = ikePoolAvailable(&pool);
    e = (size_t) 0L;
    ck_assert_msg(a == e, "memory marked as avilable after destroying pool");
}
END_TEST

START_TEST(test_poolGet)
{
    ikePool pool;
    ck_assert_msg(ikePoolInit(&pool, IKE_POOL_SMALL) == IKE_POOL_OK, "could not init pool");

    char *ptr = ikePoolGet(&pool, sizeof(char));
    ck_assert_msg(ptr != NULL, "not enough memory");
    ck_assert_msg(ptr >= pool.current->start && ptr < pool.current->end, "memory request not in range of current pool block");

    ikePoolDestroy(&pool);
}
END_TEST

START_TEST(test_poolGetUnaligned)
{
    ikePool pool;
    ck_assert_msg(ikePoolInit(&pool, IKE_POOL_SMALL) == IKE_POOL_OK, "could not init pool");

    char *ptr1 = ikePoolGet(&pool, sizeof(char)*3);
    ck_assert_msg(ptr1 != NULL, "not enough memory");

    char *ptr2 = ikePoolGet(&pool, sizeof(char)*11);
    ck_assert_msg(ptr2 != NULL, "not enough memory");

    ck_assert_msg(is_aligned(ptr1, IKE_POOL_ALIGMENT) && is_aligned(ptr2, IKE_POOL_ALIGMENT), "memory is not aligned when requesting unaligned block");
    ikePoolDestroy(&pool);
}
END_TEST

START_TEST(test_poolGetBiggerBlock)
{
    ikePool pool;
    ck_assert_msg(ikePoolInit(&pool, sizeof(char)*4) == IKE_POOL_OK, "could not init pool");

    char *ptr = ikePoolGet(&pool, sizeof(char)*8);
    ck_assert_msg(ptr != NULL, "not enough memory or bad allocation");
    ck_assert_msg(pool.first != pool.current, "major memory request should allocate a new block");
    ck_assert_msg(ikePoolBlockTotalSize(pool.current) != ikePoolBlockTotalSize(pool.first), "blocks should have different size");
    ck_assert_msg(ikePoolTotalSize(&pool) == (size_t) 16, "both blocks should sum a total of 16 bytes");

    ikePoolDestroy(&pool);
}
END_TEST

START_TEST(test_poolRecycle)
{
    ikePool pool;
    ck_assert_msg(ikePoolInit(&pool, IKE_POOL_SMALL) == IKE_POOL_OK, "could not init pool");

    size_t a = ikePoolAvailable(&pool);
    size_t e = IKE_POOL_SMALL;
    ck_assert_msg(a == e, "bad memory allocation for pool");

    ikePoolGet(&pool, sizeof(char)*16);
    a = ikePoolAvailable(&pool);
    ck_assert_msg(a != e, "available memory should be less than starting point");

    ikePoolRecycle(&pool);
    a = ikePoolAvailable(&pool);
    ck_assert_msg(a == e, "pool should have initial memory available after recycling");
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/pool");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_initRelease);
    tcase_add_test(tc_core, test_poolGet);
    tcase_add_test(tc_core, test_poolGetUnaligned);
    tcase_add_test(tc_core, test_poolGetBiggerBlock);
    tcase_add_test(tc_core, test_poolRecycle);
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

