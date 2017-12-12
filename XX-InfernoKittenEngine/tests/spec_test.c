#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <tests/config.h>
#include <ike/spec.h>

START_TEST(test_initDestroy)
{
    ikeSpec spec;
    ck_assert_msg(ikeSpecInit(&spec) == IKE_SPEC_OK, "failed spec init");
    ck_assert_msg(spec.pool != NULL, "spec pool is not initialized");
    ck_assert_msg(spec.hashmap != NULL, "spec hashmap is not initialized");

    ikeSpecDestroy(&spec);
    ck_assert_msg(spec.pool == NULL, "did not finalize pool");
    ck_assert_msg(spec.hashmap == NULL, "did not finalize hashmap");
}
END_TEST

START_TEST(test_putGetInt)
{
    ikeSpec spec;
    ikeSpecInit(&spec);
    int value = 0, expected = 7;

    ck_assert_msg(ikeSpecPutInt(&spec, "test", 7) == IKE_SPEC_OK, "could not store int");
    ck_assert_msg(ikeSpecGetInt(&spec, "test", &value) == IKE_SPEC_OK, "could not read int");
    ck_assert_msg(value == expected, "stored integer is not equal than expected");

    ikeSpecDestroy(&spec);
}
END_TEST

START_TEST(test_putGetFloat)
{
    ikeSpec spec;
    ikeSpecInit(&spec);
    float value = 0.f, expected = 5.4f;

    ck_assert_msg(ikeSpecPutFloat(&spec, "test", 5.4f) == IKE_SPEC_OK, "could not store float");
    ck_assert_msg(ikeSpecGetFloat(&spec, "test", &value) == IKE_SPEC_OK, "could not read float");
    ck_assert_msg(value == expected, "stored float is not equal than expected");

    ikeSpecDestroy(&spec);
}
END_TEST

START_TEST(test_putGetString)
{
    ikeSpec spec;
    ikeSpecInit(&spec);
    const char *value = NULL;
    const char *expected = "some string";

    ck_assert_msg(ikeSpecPutString(&spec, "test", "some string") == IKE_SPEC_OK, "could not store string");
    ck_assert_msg(ikeSpecGetString(&spec, "test", &value) == IKE_SPEC_OK, "could not read string");
    ck_assert_msg(strcmp(value, expected) == 0, "stored string is not equal than expected");

    ikeSpecDestroy(&spec);
}
END_TEST

START_TEST(test_putGetSpec)
{
    ikeSpec parent, child, value;
    ikeSpecInit(&parent);
    ikeSpecInit(&child);

    ck_assert_msg(ikeSpecPutSpec(&parent, "test", &child) == IKE_SPEC_OK, "could not store spec");
    ck_assert_msg(ikeSpecGetSpec(&parent, "test", &value) == IKE_SPEC_OK, "could not read spec");
    ck_assert_msg(child.pool == value.pool && child.hashmap == value.hashmap, "read spec is not the same as inserted pool");

    ikeSpecDestroy(&parent);
    ck_assert_msg(child.pool == NULL && child.hashmap == NULL, "children should be destroyed with parents");
}
END_TEST

Suite *specSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/spec");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_initDestroy);
    tcase_add_test(tc_core, test_putGetInt);
    // tcase_add_test(tc_core, test_putGetFloat);
    // tcase_add_test(tc_core, test_putGetString);
    // tcase_add_test(tc_core, test_putGetSpec);
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

