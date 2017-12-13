#include <string.h>
#include <stdlib.h>
#include <check.h>
#include <tests/config.h>
#include <ike/asset.h>
#include <ike/presenter.h>

START_TEST(test_initDestroy)
{
    ikeAssetSetBase(CONTENT_PATH);

    ck_assert_msg(ikePresenterInit("presenter-config") == IKE_PRESENTER_OK, "could not initialize presenter");

    ikePresenter *presenter = ikeGetPresenter();
    ck_assert_msg(presenter->window != NULL, "window was not initialized");
    ck_assert_msg(presenter->height == 600, "window height was not configured");
    ck_assert_msg(presenter->width == 800, "window width was not configured");

    ikePresenterDestroy();
}
END_TEST

START_TEST(test_quickFrame)
{
    ikeAssetSetBase(CONTENT_PATH);
    ck_assert_msg(ikePresenterInit("presenter-config") == IKE_PRESENTER_OK, "could not initialize presenter");
    ck_assert_msg(ikePresenterRunning() == IKE_PRESENTER_RUNNING, "presenter is not running");
    ikePresenterUpdate();
    ikePresenterPrepareFrame();
    ck_assert_msg(ikePresenterCommitFrame() == IKE_PRESENTER_OK, "could not commit frame");
    ikePresenterDestroy();
}
END_TEST

Suite *presenterSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/presenter");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_initDestroy);
    tcase_add_test(tc_core, test_quickFrame);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = presenterSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

