#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <tests/config.h>
#include <ike/display.h>
#include <ike/asset.h>

#include <stdio.h>

START_TEST(test_displayConfig)
{
    ikeAssetSetBase(CONTENT_PATH);

    ikeDisplay display;
    ck_assert_msg(ikeDisplayConfig(&display) == IKE_DISPLAY_OK, "could not configure display");

    fprintf(stderr, "Display config: %dx%d - '%s'.\n", display.height, display.width, display.title);
    ck_assert_msg(display.height == 800, "did not configure display height");
    ck_assert_msg(display.width == 600, "did not configure display width");
    ck_assert_msg(strcmp(display.title, "testing window") == 0, "did not configure display title");
    ikeDisplayTerminate(&display);
}
END_TEST

Suite *mat4Suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/display");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_displayConfig);
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

