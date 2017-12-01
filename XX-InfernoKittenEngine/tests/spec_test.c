#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <ike/spec.h>

#include <stdio.h>

START_TEST(test_specSimple)
{
    ikeSpec spec;
    ikeSpecInit(&spec);

    int *itest = calloc(1, sizeof(int)); *itest = 7;
    float *ftest = calloc(1, sizeof(float)); *ftest = 3.4f;
    double *dtest = calloc(1, sizeof(double)); *dtest = 3.4;
    char *stest = calloc(12, sizeof(char)); strcpy(stest, "hello world");

    ck_assert_msg(ikeSpecPut(&spec, "int", itest) == IKE_SPEC_MAP_OK, "could not store int");
    ck_assert_msg(ikeSpecPut(&spec, "float", ftest) == IKE_SPEC_MAP_OK, "could not store float");
    ck_assert_msg(ikeSpecPut(&spec, "double", dtest) == IKE_SPEC_MAP_OK, "could not store double");
    ck_assert_msg(ikeSpecPut(&spec, "string", stest) == IKE_SPEC_MAP_OK, "could not store string");

    int *itestr;
    float *ftestr;
    double *dtestr;
    char *stestr;

    ck_assert_msg(ikeSpecGet(&spec, "int", (ikeAny *) &itestr) == IKE_SPEC_MAP_OK, "could not read int");
    ck_assert_msg(ikeSpecGet(&spec, "float", (ikeAny *) &ftestr) == IKE_SPEC_MAP_OK, "could not read float");
    ck_assert_msg(ikeSpecGet(&spec, "double", (ikeAny *) &dtestr) == IKE_SPEC_MAP_OK, "could not read double");
    ck_assert_msg(ikeSpecGet(&spec, "string", (ikeAny *) &stestr) == IKE_SPEC_MAP_OK, "could not read string");

    ck_assert_msg(*itest == *itestr, "stored integer is not equal than expected");
    ck_assert_msg(*ftest == *ftestr, "stored float is not equal than expected");
    ck_assert_msg(*dtest == *dtestr, "stored double is not equal than expected");
    ck_assert_msg(strcmp(stest, stestr) == 0, "stored string is not equal than expected");

    free(itest);
    free(ftest);
    free(dtest);
    free(stest);

    ikeSpecFree(&spec);
}
END_TEST

START_TEST(test_specGetInt)
{
    ikeSpec spec;
    ikeSpecInit(&spec);

    int *itest = calloc(1, sizeof(int)); *itest = 7;
    int itestr;

    ck_assert_msg(ikeSpecPut(&spec, "int", itest) == IKE_SPEC_MAP_OK, "could not store int");
    ck_assert_msg(ikeSpecGetInt(&spec, "int", &itestr) == IKE_SPEC_MAP_OK, "could not read int");
    ck_assert_msg(*itest == itestr, "stored integer is not equal than expected");
    free(itest);
}
END_TEST

START_TEST(test_specGetFloat)
{
    ikeSpec spec;
    ikeSpecInit(&spec);

    float *ftest = calloc(1, sizeof(float)); *ftest = 5.6;
    float ftestr;

    ck_assert_msg(ikeSpecPut(&spec, "float", ftest) == IKE_SPEC_MAP_OK, "could not store float");
    ck_assert_msg(ikeSpecGetFloat(&spec, "float", &ftestr) == IKE_SPEC_MAP_OK, "could not read float");
    ck_assert_msg(*ftest == ftestr, "stored float is not equal than expected");
    free(ftest);
}
END_TEST

START_TEST(test_specGetDouble)
{
    ikeSpec spec;
    ikeSpecInit(&spec);

    double *dtest = calloc(1, sizeof(double)); *dtest = 5.6;
    double dtestr;

    ck_assert_msg(ikeSpecPut(&spec, "double", dtest) == IKE_SPEC_MAP_OK, "could not store double");
    ck_assert_msg(ikeSpecGetDouble(&spec, "double", &dtestr) == IKE_SPEC_MAP_OK, "could not read double");
    ck_assert_msg(*dtest == dtestr, "stored double is not equal than expected");
    free(dtest);
}
END_TEST


START_TEST(test_specGetString)
{
    ikeSpec spec;
    ikeSpecInit(&spec);

    char *stest = calloc(12, sizeof(char)); strcpy(stest, "hello world");
    char *stestr;

    ck_assert_msg(ikeSpecPut(&spec, "string", stest) == IKE_SPEC_MAP_OK, "could not store string");
    ck_assert_msg(ikeSpecGetString(&spec, "string", &stestr) == IKE_SPEC_MAP_OK, "could not read string");
    ck_assert_msg(strcmp(stest, stestr) == 0, "stored string is not equal than expected");
    free(stest);
}
END_TEST

// TODO: Remaining tests for Spec

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/spec");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_specSimple);
    tcase_add_test(tc_core, test_specGetInt);
    tcase_add_test(tc_core, test_specGetFloat);
    tcase_add_test(tc_core, test_specGetDouble);
    tcase_add_test(tc_core, test_specGetString);
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

