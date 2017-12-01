#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <tests/config.h>
#include <ike/mathutil.h>
#include <ike/asset.h>
#include <ike/spec.h>

START_TEST(test_getText)
{
    ikeAssetSetBase(CONTENT_PATH);
    const char *expect = "This is plain text";
    char *data = NULL;
    size_t len;

    int res = ikeAssetGetText("plain-text", &data, &len);
    ck_assert_msg(res == IKE_ASSET_OK, "could not read plain text data");
    if(res == IKE_ASSET_OK) {
        ck_assert_msg(len != 0, "did not read text data");
        ck_assert_msg(data != NULL, "read data is null");

        if (len > 0) {
            int tmp = strncmp(expect, data, MIN(size_t, len, strlen(expect)));
            ck_assert_msg(tmp == 0, "read data is not equal to expected data.");
        }
    }

    ikeAssetFree(&data);
}
END_TEST

START_TEST(test_getSpec)
{
    ikeAssetSetBase(CONTENT_PATH);

    ikeSpec spec;
    ikeSpecInit(&spec);

    int res = ikeAssetGetSpec("data", &spec);
    ck_assert_msg(res == IKE_ASSET_OK, "could not read spec data");
    if (res == IKE_ASSET_OK) {
        int ival = 0;
        ikeSpecGetInt(&spec, "integer", &ival);
        ck_assert_msg(ival == 10, "bad integer read");

        char *cval = NULL;
        ikeSpecGetString(&spec, "string", &cval);
        ck_assert_msg(strcmp("content", cval) == 0, "bad string read");

        double dval = 0.0;
        ikeSpecGetDouble(&spec, "decimal", &dval);
        ck_assert_msg(dval == 3.3, "bad double read");

        int bval = 0;
        ikeSpecGetInt(&spec, "boolean", &bval);
        ck_assert_msg(bval == 1, "bad boolean read");
    }

    ikeSpecFree(&spec);
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/asset");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_getText);
    tcase_add_test(tc_core, test_getSpec);
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

