#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <tests/config.h>
#include <ike/mathutil.h>
#include <ike/asset.h>

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
            int tmp = strncmp(expect, data, MAX(size_t, len, strlen(expect)));
            ck_assert_msg(tmp == 0, "read data is not equal to expected data.");
        }
    }

    ikeAssetFree(&data);
}
END_TEST

START_TEST(test_getImage)
{
    ikeAssetSetBase(CONTENT_PATH);
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/asset");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_getText);
    tcase_add_test(tc_core, test_getImage);
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

