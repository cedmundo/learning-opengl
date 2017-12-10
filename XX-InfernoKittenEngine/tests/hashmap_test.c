#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <ike/hashmap.h>

#include <stdio.h>

START_TEST(test_hashmapSimple)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    int *itest = calloc(1, sizeof(int)); *itest = 7;
    ck_assert_msg(ikeHashMapPut(&hashmap, "int", itest) == IKE_HASHMAP_OK, "could not store int");

    float *ftest = calloc(1, sizeof(float)); *ftest = 3.4f;
    ck_assert_msg(ikeHashMapPut(&hashmap, "float", ftest) == IKE_HASHMAP_OK, "could not store float");

    double *dtest = calloc(1, sizeof(double)); *dtest = 3.4;
    ck_assert_msg(ikeHashMapPut(&hashmap, "double", dtest) == IKE_HASHMAP_OK, "could not store double");

    char *stest = calloc(12, sizeof(char)); strcpy(stest, "hello world");
    ck_assert_msg(ikeHashMapPut(&hashmap, "string", stest) == IKE_HASHMAP_OK, "could not store string");

    int *itestr;
    ck_assert_msg(ikeHashMapGet(&hashmap, "int", (ikeAny *) &itestr) == IKE_HASHMAP_OK, "could not read int");
    ck_assert_msg(*itest == *itestr, "stored integer is not equal than expected");

    float *ftestr;
    ck_assert_msg(ikeHashMapGet(&hashmap, "float", (ikeAny *) &ftestr) == IKE_HASHMAP_OK, "could not read float");
    ck_assert_msg(*ftest == *ftestr, "stored float is not equal than expected");

    double *dtestr;
    ck_assert_msg(ikeHashMapGet(&hashmap, "double", (ikeAny *) &dtestr) == IKE_HASHMAP_OK, "could not read double");
    ck_assert_msg(*dtest == *dtestr, "stored double is not equal than expected");

    char *stestr;
    ck_assert_msg(ikeHashMapGet(&hashmap, "string", (ikeAny *) &stestr) == IKE_HASHMAP_OK, "could not read string");
    ck_assert_msg(strcmp(stest, stestr) == 0, "stored string is not equal than expected");

    free(itest);
    free(ftest);
    free(dtest);
    free(stest);

    ikeHashMapFree(&hashmap);
}
END_TEST

START_TEST(test_hashmapGetInt)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    int *itest = calloc(1, sizeof(int)); *itest = 7;
    int itestr;

    ck_assert_msg(ikeHashMapPut(&hashmap, "int", itest) == IKE_HASHMAP_OK, "could not store int");
    ck_assert_msg(ikeHashMapGetInt(&hashmap, "int", &itestr) == IKE_HASHMAP_OK, "could not read int");
    ck_assert_msg(*itest == itestr, "stored integer is not equal than expected");
    free(itest);
}
END_TEST

START_TEST(test_hashmapGetFloat)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    float *ftest = calloc(1, sizeof(float)); *ftest = 5.6;
    float ftestr;

    ck_assert_msg(ikeHashMapPut(&hashmap, "float", ftest) == IKE_HASHMAP_OK, "could not store float");
    ck_assert_msg(ikeHashMapGetFloat(&hashmap, "float", &ftestr) == IKE_HASHMAP_OK, "could not read float");
    ck_assert_msg(*ftest == ftestr, "stored float is not equal than expected");
    free(ftest);
}
END_TEST

START_TEST(test_hashmapGetDouble)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    double *dtest = calloc(1, sizeof(double)); *dtest = 5.6;
    double dtestr;

    ck_assert_msg(ikeHashMapPut(&hashmap, "double", dtest) == IKE_HASHMAP_OK, "could not store double");
    ck_assert_msg(ikeHashMapGetDouble(&hashmap, "double", &dtestr) == IKE_HASHMAP_OK, "could not read double");
    ck_assert_msg(*dtest == dtestr, "stored double is not equal than expected");
    free(dtest);
}
END_TEST

START_TEST(test_hashmapGetString)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    char *stest = calloc(12, sizeof(char)); strcpy(stest, "hello world");
    char *stestr;

    ck_assert_msg(ikeHashMapPut(&hashmap, "string", stest) == IKE_HASHMAP_OK, "could not store string");
    ck_assert_msg(ikeHashMapGetString(&hashmap, "string", &stestr) == IKE_HASHMAP_OK, "could not read string");
    ck_assert_msg(strcmp(stest, stestr) == 0, "stored string is not equal than expected");
    free(stest);
}
END_TEST

static int test_hashmapIterateCount = 0;
static int test_hashmapIterateHelper(ikeAny udata, ikeAny item) {
    test_hashmapIterateCount ++;
    return IKE_HASHMAP_OK;
}

START_TEST(test_hashmapIterate)
{
    ikeHashMap hashmap;
    ikeHashMapInit(&hashmap);

    char *stest1 = calloc(12, sizeof(char)); strcpy(stest1, "hello world");
    char *stest2 = calloc(12, sizeof(char)); strcpy(stest2, "dlrow olleh");

    ck_assert_msg(ikeHashMapPut(&hashmap, "regular", stest1) == IKE_HASHMAP_OK, "could not store string (regular)");
    ck_assert_msg(ikeHashMapPut(&hashmap, "reverse", stest2) == IKE_HASHMAP_OK, "could not store string (reverse)");

    ck_assert_msg(ikeHashMapIterate(&hashmap, test_hashmapIterateHelper, NULL) == IKE_HASHMAP_OK, "could not iterate map");
    ck_assert_msg(test_hashmapIterateCount == 2, "unexpected iteration keys count");

    free(stest1);
    free(stest2);
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/hashmap");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_hashmapSimple);
    tcase_add_test(tc_core, test_hashmapGetInt);
    tcase_add_test(tc_core, test_hashmapGetFloat);
    tcase_add_test(tc_core, test_hashmapGetDouble);
    tcase_add_test(tc_core, test_hashmapGetString);
    tcase_add_test(tc_core, test_hashmapIterate);
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

