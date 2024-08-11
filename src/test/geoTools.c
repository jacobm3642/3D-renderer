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

START_TEST(vec_subtract_test)
{
    vec2 v1 = {3, 3};
    vec2 v2 = {1, 1};
    
    // Test case 1: Subtracting v2 from v1
    vec2 v3 = vec_subtract(v1, v2);
    ck_assert_int_eq(v3.x, 2);
    ck_assert_int_eq(v3.y, 2);

    // Test case 2: Subtracting v1 from v1
    vec2 v4 = vec_subtract(v1, v1);
    ck_assert_int_eq(v4.x, 0);
    ck_assert_int_eq(v4.y, 0);
} END_TEST

START_TEST(signed_area_test)
{
    vec2 a = {0, 0};
    vec2 b = {1, 0};
    vec2 c = {0, 1};
    
    // Test case 1: Calculating signed area of triangle a, b, c
    i32 area1 = signed_area(a, b, c);
    ck_assert_int_eq(area1, 1);

    // Test case 2: Reversing order to calculate signed area of triangle c, b, a
    i32 area2 = signed_area(c, b, a);
    ck_assert_int_eq(area2, -1);
} END_TEST

START_TEST(dot_test)
{
    vec2 a = {1, 2};
    vec2 b = {3, 4};
    
    // Test case 1: Calculating dot product of a and b
    i32 result1 = dot(a, b);
    ck_assert_int_eq(result1, 11);

    // Test case 2: Calculating dot product of a with itself
    i32 result2 = dot(a, a);
    ck_assert_int_eq(result2, 5);
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

START_TEST(lerp_test)
{
    float v0 = 1.0;
    float v1 = 3.0;
    float t = 0.5;
    
    // Test case 1: Linear interpolation between v0 and v1 at t = 0.5
    float result1 = lerp(v0, v1, t);
    ck_assert_double_eq_tol(result1, 2.0, 0.0001);

    // Test case 2: Linear interpolation at t = 0.0 (should be v0)
    float result2 = lerp(v0, v1, 0.0);
    ck_assert_double_eq_tol(result2, v0, 0.0001);
} END_TEST

START_TEST(scale_test)
{
    vec2 a = {2, 3};
    float scale_factor = 2.0;
    
    // Test case 1: Scaling vector a by scale_factor
    scale(&a, scale_factor);
    ck_assert_double_eq_tol(a.x, 4.0, 0.0001);
    ck_assert_double_eq_tol(a.y, 6.0, 0.0001);

    // Test case 2: Scaling vector a by 0.0 (should result in zero vector)
    scale(&a, 0.0);
    ck_assert_double_eq_tol(a.x, 0.0, 0.0001);
    ck_assert_double_eq_tol(a.y, 0.0, 0.0001);
} END_TEST

START_TEST(normalize_test)
{
    vec2 p_vec = {3, 4};
    
    // Test case 1: Normalizing vector p_vec
    normalize(&p_vec);
    ck_assert_double_eq_tol(p_vec.x, 0.6, 0.0001);
    ck_assert_double_eq_tol(p_vec.y, 0.8, 0.0001);

    // Test case 2: Normalizing a zero vector (should remain unchanged)
    vec2 q_vec = {0, 0};
    normalize(&q_vec);
    ck_assert_double_eq_tol(q_vec.x, 0.0, 0.0001);
    ck_assert_double_eq_tol(q_vec.y, 0.0, 0.0001);
} END_TEST



Suite *geo_test_suite()
{
        Suite *s;
        TCase *tc;

        s = suite_create("geometric_tests");
        tc = tcase_create("Core");

        tcase_add_test(tc, vec_add_test);
        tcase_add_test(tc, vec_subtract_test);
        tcase_add_test(tc, vec_is_ccw_test);
        tcase_add_test(tc, lerp_test);
        tcase_add_test(tc, normalize_test);
        tcase_add_test(tc, scale_test);
        tcase_add_test(tc, dot_test);
        tcase_add_test(tc, signed_area_test);
        tcase_add_test(tc, vec_line_intersect_test);

        suite_add_tcase(s, tc);

        return s;
}

vec2 run_geo_tests()
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
        vec2 out = {run-failed, run};
        return out;
}
