#include <check.h>
#include <stdio.h>

#include "dataTypes.h"
#include "geometric_tools.h"

#include "tanea.h"

START_TEST(vec_add_test)
{
        vec2 v1 = {1, 1};
        vec2 v2 = vec_add(v1, v1);
        ck_assert_int_eq(v2.x, 2);
        ck_assert_int_eq(v2.y, 2);

        vec2 v3 = vec_add(v1, v2);
        ck_assert_int_eq(v3.x, 3);
        ck_assert_int_eq(v3.y, 3);

} END_TEST

START_TEST(vec_is_ccw_test)
{
        vec2 v1 = {0, 0};
        vec2 v2 = {1, 0};
        vec2 v3 = {0, 1};
        ck_assert(is_ccw(v1, v2, v3) == true);
        ck_assert(is_ccw(v1, v3, v2) == false);
} END_TEST

START_TEST(vec_line_intersect_test)
{
        vec2 p1 = {0, 0};
        vec2 p2 = {1000, 1000};
        vec2 p3 = {100, 0};
        vec2 p4 = {0, 200};
        ck_assert(line_intersect(p1, p2, p3, p4) == true);
        ck_assert(line_intersect(p1, p3, p1, p4) == false);
        ck_assert(line_intersect(p2, p1, p4, p3) == true);
} END_TEST


Suite *geo_test_suite()
{
        Suite *s;
        TCase *tc;

        s = suite_create("geometric_tests");
        tc = tcase_create("Core");

        tcase_add_test(tc, vec_add_test);
        tcase_add_test(tc, vec_is_ccw_test);
        tcase_add_test(tc, vec_line_intersect_test);

        suite_add_tcase(s, tc);

        return s;
}

void run_geo_tests()
{
        int failed = 0;
        int run = 0;
        Suite *s;
        SRunner *runner;

        printf("running geo tests\n");

        s = geo_test_suite();
        runner = srunner_create(s);

        srunner_run_all(runner, CK_NORMAL);

        run = srunner_ntests_run(runner);
        failed = srunner_ntests_failed(runner);

        srunner_free(runner);
        printf("\n%d of %d Passed\n", run-failed, run);
}
