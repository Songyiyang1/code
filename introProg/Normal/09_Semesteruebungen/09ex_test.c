/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "09ex.c"
#include "testrunner.c"
#include "String.h"
#include "tree.h"
#include "tree_utils.h"
#include "array.h"
#include "array_utils.h"

#define TEST_NAME "09ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_1 27
#define TEST_CASES_2 5

void assert_array(Tester *t, Array expected, Array got, const char *context) {
    if (expected.len != got.len || !uint16_array_equality(expected.arr, got.arr, expected.len)) {
        String s_exp = str_new();
        render_array(&s_exp, expected);
        String s_got = str_new();
        render_array(&s_got, got);
        
        handle_assertion_failure(t, s_exp.buf, s_got.buf, context);

        str_free(s_exp);
        str_free(s_got);
    }
}

typedef struct TestCase1_ {
    Array arr;
    bool expected;
} TestCase1;

typedef struct TestCase2_ {
    TreeNode *t;
    Array expected;
} TestCase2;

char* render_exercise_1(TestCase1 test)
{
    String s = str_new();
    render_array(&s, test.arr);
    return s.buf;
}

char* render_exercise_2(TestCase2 test)
{
    String s = str_new();

    str_str(&s, "\nEingabebaum: \n");
    char *drawing = tree_ascii(test.t);
    str_str(&s, drawing);
    free(drawing);

    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 test) {
    char *args = render_exercise_1(test);
    bool got = is_max_heap(test.arr);

    assert_bool(tester, test.expected, got, args);

    free(args);
}

void do_test_2(Tester *tester, TestCase2 test) {
    char *args = render_exercise_2(test);

    TreeNode *copy = tree_clone(test.t);

    Array got;
    got.len = test.expected.len;
    got.arr = malloc(sizeof(uint16_t) * test.expected.len);
    for (size_t i = 0; i < test.expected.len; i++) {
        got.arr[i] = 0;
    }

    tree_to_array(copy, got);

    assert_array(tester, test.expected, got, args);

    free(args);
    free(got.arr);
    tree_free(test.t);
    tree_free(copy);
}

Array arrs1[TEST_CASES_1] = {
    {.arr=(uint16_t[1]){7}, .len=0}, /* length 0 is deliberate, because you cannot have array literals with zero entries*/
    {.arr=(uint16_t[1]){7}, .len=1},
    {.arr=(uint16_t[4]){1, 2, 3, 4}, .len=4},
    {.arr=(uint16_t[4]){1, 2, 4, 3}, .len=4},
    {.arr=(uint16_t[4]){1, 3, 2, 4}, .len=4},
    {.arr=(uint16_t[4]){1, 3, 4, 2}, .len=4},
    {.arr=(uint16_t[4]){1, 4, 2, 3}, .len=4},
    {.arr=(uint16_t[4]){1, 4, 3, 2}, .len=4},
    {.arr=(uint16_t[4]){2, 1, 3, 4}, .len=4},
    {.arr=(uint16_t[4]){2, 1, 4, 3}, .len=4},
    {.arr=(uint16_t[4]){2, 3, 1, 4}, .len=4},
    {.arr=(uint16_t[4]){2, 3, 4, 1}, .len=4},
    {.arr=(uint16_t[4]){2, 4, 1, 3}, .len=4},
    {.arr=(uint16_t[4]){2, 4, 3, 1}, .len=4},
    {.arr=(uint16_t[4]){3, 1, 2, 4}, .len=4},
    {.arr=(uint16_t[4]){3, 1, 4, 2}, .len=4},
    {.arr=(uint16_t[4]){3, 2, 1, 4}, .len=4},
    {.arr=(uint16_t[4]){3, 2, 4, 1}, .len=4},
    {.arr=(uint16_t[4]){3, 4, 2, 3}, .len=4},
    {.arr=(uint16_t[4]){3, 4, 3, 2}, .len=4},
    {.arr=(uint16_t[4]){4, 1, 2, 3}, .len=4},
    {.arr=(uint16_t[4]){4, 1, 3, 2}, .len=4},
    {.arr=(uint16_t[4]){4, 2, 1, 3}, .len=4},
    {.arr=(uint16_t[4]){4, 2, 3, 1}, .len=4},
    {.arr=(uint16_t[4]){4, 3, 1, 2}, .len=4},
    {.arr=(uint16_t[4]){4, 3, 2, 1}, .len=4},
    {.arr=(uint16_t[4]){7, 7, 7, 7}, .len=4},
};
bool expecteds1[TEST_CASES_1] = {
    true, true,
    false, false, false, false, false, false,
    false, false, false, false, false, false,
    false, false, false, false, false, false,
    false, false, false, true, true, true,
    true,
};

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "is_max_heap", "Aufgabe 1: Max-Heap-Eigenschaft prüfen."))
    {
        for (size_t i = 0; i < TEST_CASES_1; i++) {
            if (begin_testcase(&tester)) {
                TestCase1 test;
                test.arr = arrs1[i];
                test.expected = expecteds1[i];
                do_test_1(&tester, test);
            }
        }
    }
    
    /* Aufgabe 2 */
    if (begin_exercise(&tester, "tree_to_array", "Aufgabe 2: Zwei Teillösungen kombinieren."))
    {
        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = NULL;
            test.expected.arr = (uint16_t[]){2};
            test.expected.len = 0;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_2();
            test.expected.arr = (uint16_t[]){2};
            test.expected.len = 1;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3();
            test.expected.arr = (uint16_t[]){6, 3};
            test.expected.len = 2;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8();
            test.expected.arr = (uint16_t[]){6, 3, 8};
            test.expected.len = 3;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2};
            test.expected.len = 4;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2_4();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2, 4};
            test.expected.len = 5;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2_4_7();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2, 4, 7};
            test.expected.len = 6;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2_4_7_9();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9};
            test.expected.len = 7;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2_4_7_9_1();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9, 1};
            test.expected.len = 8;

            do_test_2(&tester, test);
        }
        
        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = t_6_3_8_2_4_7_9_1_42_notasearchtree();
            test.expected.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9, 1, 42};
            test.expected.len = 9;

            do_test_2(&tester, test);
        }

    }

    return wrap_up(&tester);
}
