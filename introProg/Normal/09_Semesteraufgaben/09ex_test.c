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

void assert_tree(Tester *t, TreeNode *expected, TreeNode *got, const char *context) {
    if (!tree_eq(expected, got)) {
        const char* s_expected = tree_ascii(expected);
        const char* s_got = tree_ascii(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

typedef struct TestCase1_ {
    TreeNode *t;
    bool expected;
} TestCase1;

typedef struct TestCase2_ {
    Array arr;
    TreeNode *expected;
} TestCase2;

char* render_exercise_1(TestCase1 test)
{
    return tree_ascii(test.t);
}

char* render_exercise_2(TestCase2 test)
{
    String s = str_new();

    str_str(&s, "\nEingabearray: \n");
    str_u16s(&s, test.arr.arr, test.arr.len);

    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 test) {
    char *args = render_exercise_1(test);
    TreeNode *copy = tree_clone(test.t);
    bool got = is_min_heap(copy);

    assert_bool(tester, test.expected, got, args);

    free(args);
    tree_free(test.t);
    tree_free(copy);
}

void do_test_2(Tester *tester, TestCase2 test) {
    char *args = render_exercise_2(test);
    Array copy = copy_array(test.arr);

    TreeNode *got = array_to_tree(copy);
    assert_tree(tester, test.expected, got, args);

    free(args);
    free(copy.arr);
    tree_free(got);
    tree_free(test.expected);
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "is_min_heap", "Aufgabe 1: Min-Heap-Eigenschaft prüfen."))
    {
        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = NULL;
            test.expected = true;

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_2();
            test.expected = true;

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_6_3();
            test.expected = false;

            do_test_1(&tester, test);
        }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_3_6();
        //     test.expected = true;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_3_6_8();
        //     test.expected = true;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_3_8_6();
        //     test.expected = false;

        //     do_test_1(&tester, test);
        // }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_6_3_8();
            test.expected = false;

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_2_2_2();

            test.expected = true;

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_2_2_2_3a();

            test.expected = true;

            do_test_1(&tester, test);
        }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_3b();

        //     test.expected = true;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_3c();

        //     test.expected = true;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_3d();

        //     test.expected = true;

        //     do_test_1(&tester, test);
        // }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_2_2_2_1a();

            test.expected = false;

            do_test_1(&tester, test);
        }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_1b();

        //     test.expected = false;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_1c();

        //     test.expected = false;

        //     do_test_1(&tester, test);
        // }

        // if (begin_testcase(&tester)) {
        //     TestCase1 test;
        //     test.t = t_2_2_2_1d();

        //     test.expected = false;

        //     do_test_1(&tester, test);
        // }
    }
    
    /* Aufgabe 2 */
    if (begin_exercise(&tester, "array_to_tree", "Aufgabe 2: Array in Baum umwandeln."))
    {
        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = NULL;
            test.arr.arr = (uint16_t[]){2};
            test.arr.len = 0;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_2();
            test.arr.arr = (uint16_t[]){2};
            test.arr.len = 1;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3();
            test.arr.arr = (uint16_t[]){6, 3};
            test.arr.len = 2;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8();
            test.arr.arr = (uint16_t[]){6, 3, 8};
            test.arr.len = 3;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2};
            test.arr.len = 4;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2_4();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2, 4};
            test.arr.len = 5;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2_4_7();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2, 4, 7};
            test.arr.len = 6;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2_4_7_9();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9};
            test.arr.len = 7;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2_4_7_9_1();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9, 1};
            test.arr.len = 8;

            do_test_2(&tester, test);
        }
        
        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.expected = t_6_3_8_2_4_7_9_1_42_notasearchtree();
            test.arr.arr = (uint16_t[]){6, 3, 8, 2, 4, 7, 9, 1, 42};
            test.arr.len = 9;

            do_test_2(&tester, test);
        }
    }

    return wrap_up(&tester);
}
