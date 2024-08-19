#include <check.h>
#include <stdio.h>
#include <strings.h>

#include "dataTypes.h"
#include "stringTools.h"
#include "engine_internal.h"

START_TEST(test_lengthOfString)
{
    ck_assert_int_eq(lengthOfString("hello"), 5);
    ck_assert_int_eq(lengthOfString(""), 0);
    ck_assert_int_eq(lengthOfString("OpenAI"), 6);
}
END_TEST

START_TEST(test_stringToInt)
{
        ck_assert_int_eq(stringToInt("1234"), 1234);
        ck_assert_int_eq(stringToInt("0"), 0);
        ck_assert_int_eq(stringToInt("42"), 42);
}
END_TEST

START_TEST(test_inplaceStripWhitespace)
{
    char str1[] = "  hello world  ";
    inplaceStripWhitespace(str1);
    ck_assert_str_eq(str1, "helloworld");

    char str2[] = " Open AI ";
    inplaceStripWhitespace(str2);
    ck_assert_str_eq(str2, "OpenAI");

    char str3[] = "   ";
    inplaceStripWhitespace(str3);
    ck_assert_str_eq(str3, "");
}
END_TEST

START_TEST(test_inplaceStripEnds)
{
    char str1[] = "  hello world  ";
    inplaceStripEnds(str1);
    ck_assert_str_eq(str1, "hello world");

    char str2[] = "  OpenAI  ";
    inplaceStripEnds(str2);
    ck_assert_str_eq(str2, "OpenAI");

    char str3[] = "NoSpaces";
    inplaceStripEnds(str3);
    ck_assert_str_eq(str3, "NoSpaces");
}
END_TEST

START_TEST(test_splitString)
{
    int count;

    char str1[] = "a,b,c";
    char **result1 = splitString(str1, ',', &count);
    ck_assert_int_eq(count, 3);
    ck_assert_str_eq(result1[0], "a");
    ck_assert_str_eq(result1[1], "b");
    ck_assert_str_eq(result1[2], "c");
    deallocate(result1);

    char str2[] = "one|two|three";
    char **result2 = splitString(str2, '|', &count);
    ck_assert_int_eq(count, 3);
    ck_assert_str_eq(result2[0], "one");
    ck_assert_str_eq(result2[1], "two");
    ck_assert_str_eq(result2[2], "three");
    deallocate(result2);

    char str3[] = "nosplit";
    char **result3 = splitString(str3, ',', &count);
    ck_assert_int_eq(count, 1);
    ck_assert_str_eq(result3[0], "nosplit");
    deallocate(result3);
}
END_TEST

Suite *string_test_suite()
{
        Suite *s;
        TCase *tc;

        s = suite_create("stack allocator tests");
        tc = tcase_create("Core");

        // add tests here
        tcase_add_test(tc, test_lengthOfString);
        tcase_add_test(tc, test_stringToInt);
        tcase_add_test(tc, test_inplaceStripWhitespace);
        tcase_add_test(tc, test_inplaceStripEnds);
        tcase_add_test(tc, test_splitString);

        suite_add_tcase(s, tc);

        return s;
}

vec2 string_test()
{
        int failed = 0;
        int run = 0;
        Suite *s;
        SRunner *runner;

        printf("running stack allocator tests\n");

        s = string_test_suite();
        runner = srunner_create(s);

        srunner_run_all(runner, CK_NORMAL);

        run = srunner_ntests_run(runner);
        failed = srunner_ntests_failed(runner);

        srunner_free(runner);
        printf("\n%d of %d Passed\n", run-failed, run);
        vec2 out = {run-failed, run};
        return  out;
}
