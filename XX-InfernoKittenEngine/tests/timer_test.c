#include <stdlib.h>
#include <check.h>
#include <ike/timer.h>
#include <GLFW/glfw3.h>

START_TEST(test_timerClick)
{
    ck_assert_msg(GL_FALSE != glfwInit(), "could not initialize glfw");

    ck_assert_msg(ikeDeltaTime() == 0.0, "bad init value for delta time");
    ck_assert_msg(ikeEllapsedTime() == 0.0, "bad init value for ellapsed time");

    ikeGlobalTimerUpdate();

    ck_assert_msg(ikeDeltaTime() != 0.0, "bad click value for delta time");
    ck_assert_msg(ikeEllapsedTime() != 0.0, "bad click value for ellapsed time");

    glfwTerminate();
}
END_TEST

Suite *timerSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ike/timer");

    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_timerClick);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int numfailed;
    Suite *s;
    SRunner *sr;

    s = timerSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    numfailed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

