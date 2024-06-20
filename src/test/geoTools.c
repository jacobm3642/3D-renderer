#include <check.h>
#include <stdio.h>

#include "geometric_tools.h"

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


Suite *geo_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("geometric_tests");
  tc = tcase_create("Core");
  
  tcase_add_test(tc, vec_add_test);
  
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
  printf("%d of %d Passed\n", run-failed, run);
}
