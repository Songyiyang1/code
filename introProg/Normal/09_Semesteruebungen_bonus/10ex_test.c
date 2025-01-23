/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "10ex.c"
#include "testrunner.c"
#include "String.h"
#include "tree.h"
#include "tree_utils.h"
#include "array.h"
#include "array_utils.h"

#define TEST_NAME "10ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_2 15

void assert_tree(Tester *t, TreeNode *expected, TreeNode *got, const char *context) {
    if (!tree_eq(expected, got)) {
        const char* s_expected = tree_ascii(expected);
        const char* s_got = tree_ascii(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

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
    TreeNode *t;
    TreeNode *expected;
} TestCase1;

typedef struct TestCase2_ {
    Array arr;
    size_t i;
    Array expected;
} TestCase2;

char* render_exercise_1(TestCase1 test)
{
    String s = str_new();

    str_str(&s, "\nEingabebaum: \n");
    char *drawing = tree_ascii(test.t);
    str_str(&s, drawing);
    free(drawing);

    return s.buf;
}

char* render_exercise_2(TestCase2 test)
{
    String s = str_new();
    str_str(&s, "\ni: ");
    str_uint(&s, test.i);
    str_str(&s, "\nEingabearray:\n");
    render_array(&s, test.arr);
    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 test) {
    char *args = render_exercise_1(test);

    heapify_tree(test.t);
    assert_tree(tester, test.expected, test.t, args);

    free(args);
    tree_free(test.t);
    tree_free(test.expected);
}

void do_test_2(Tester *tester, TestCase2 test) {
    char *args = render_exercise_2(test);

    heapify_array(test.arr, test.i);
    assert_array(tester, test.expected, test.arr, args);

    free(args);
}

Array arrs2[TEST_CASES_2] = {
    {.arr=(uint16_t[1]){7}, .len=1},
    {.arr=(uint16_t[3]){3, 6, 8}, .len=3},
    {.arr=(uint16_t[3]){3, 8, 6}, .len=3},
    {.arr=(uint16_t[3]){6, 3, 8}, .len=3},
    {.arr=(uint16_t[3]){6, 8, 3}, .len=3},
    {.arr=(uint16_t[3]){8, 3, 6}, .len=3},
    {.arr=(uint16_t[3]){8, 6, 3}, .len=3},
    {.arr=(uint16_t[5]){2, 3, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){4, 3, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){6, 3, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){8, 3, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){2, 3, 9, 7, 5}, .len=5},
    {.arr=(uint16_t[5]){4, 3, 9, 7, 5}, .len=5},
    {.arr=(uint16_t[5]){6, 3, 9, 7, 5}, .len=5},
    {.arr=(uint16_t[5]){8, 3, 9, 7, 5}, .len=5},
};
Array expecteds2[TEST_CASES_2] = {
    {.arr=(uint16_t[1]){7}, .len=1},
    {.arr=(uint16_t[3]){3, 6, 8}, .len=3},
    {.arr=(uint16_t[3]){3, 8, 6}, .len=3},
    {.arr=(uint16_t[3]){3, 6, 8}, .len=3},
    {.arr=(uint16_t[3]){3, 8, 6}, .len=3},
    {.arr=(uint16_t[3]){3, 8, 6}, .len=3},
    {.arr=(uint16_t[3]){3, 6, 8}, .len=3},
    {.arr=(uint16_t[5]){2, 3, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){3, 4, 9, 5, 7}, .len=5},
    {.arr=(uint16_t[5]){3, 5, 9, 6, 7}, .len=5},
    {.arr=(uint16_t[5]){3, 5, 9, 8, 7}, .len=5},
    {.arr=(uint16_t[5]){2, 3, 9, 7, 5}, .len=5},
    {.arr=(uint16_t[5]){3, 4, 9, 7, 5}, .len=5},
    {.arr=(uint16_t[5]){3, 5, 9, 7, 6}, .len=5},
    {.arr=(uint16_t[5]){3, 5, 9, 7, 8}, .len=5},
};

TreeNode *test_tree() {
    TreeNode *t = t_1();
    t->left = t_3();
    t->left->left = t_5();
    t->left->right = t_7();
    t->right = t_9();
    return t;
}

TreeNode *test_tree2() {
    TreeNode *t = t_1();
    t->left = t_3();
    t->left->left = t_7();
    t->left->right = t_5();
    t->right = t_9();
    return t;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "heapify_tree", "Aufgabe 1: Heapify auf Baum."))
    {
        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_2();
            test.expected = t_2();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_3();
            test.t->left = t_6();
            test.expected = t_3();
            test.expected->left = t_6();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_6_3();
            test.expected = t_3();
            test.expected->left = t_6();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_6_3_8();
            test.expected = t_3_8();
            test.expected->left = t_6();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_8_3();
            test.t->right = t_6();
            test.expected = t_3_6();
            test.expected->left = t_8();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_3_8();
            test.t->left = t_6();
            test.expected = t_3_8();
            test.expected->left = t_6();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_8_6();
            test.t->right = t_3();
            test.expected = t_3_8();
            test.expected->left = t_6();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_3_6();
            test.t->left = t_8();
            test.expected = t_3_6();
            test.expected->left = t_8();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = t_6();
            test.t->left = t_8();
            test.t->right = t_3();
            test.expected = t_3_6();
            test.expected->left = t_8();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree();
            test.expected = test_tree();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree();
            test.t->item = 4;
            test.expected = test_tree();
            test.expected->item = 3;
            test.expected->left->item = 4; 

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree();
            test.t->item = 6;
            test.expected = test_tree();
            test.expected->item = 3;
            test.expected->left->item = 5;
            test.expected->left->left->item = 6; 

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree();
            test.t->item = 8;
            test.expected = test_tree();
            test.expected->item = 3;
            test.expected->left->item = 5;
            test.expected->left->left->item = 8; 

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree2();
            test.expected = test_tree2();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree2();
            test.t->item = 4;
            test.expected = test_tree2();
            test.expected->item = 3;
            test.expected->left->item = 4; 

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree2();
            test.t->item = 6;
            test.expected = test_tree2();
            test.expected->item = 3;
            test.expected->left->item = 5;
            test.expected->left->right->item = 6; 

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.t = test_tree2();
            test.t->item = 8;
            test.expected = test_tree2();
            test.expected->item = 3;
            test.expected->left->item = 5;
            test.expected->left->right->item = 8; 

            do_test_1(&tester, test);
        }

    }
    
    /* Aufgabe 2 */
    if (begin_exercise(&tester, "heapify_array", "Aufgabe 2: Heapify auf Array."))
    {
       for (size_t i = 0; i < TEST_CASES_2; i++) {
            if (begin_testcase(&tester)) {
                TestCase2 test;
                test.arr = arrs2[i];
                test.i = 0;
                test.expected = expecteds2[i];
                do_test_2(&tester, test);
            }
        }
    }

    return wrap_up(&tester);
}
