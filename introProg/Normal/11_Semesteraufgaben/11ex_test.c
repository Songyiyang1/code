/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "11ex.c"
#include "testrunner.c"
#include "String.h"
#include "height_tree_utils.h"

#define TEST_NAME "12ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif

void assert_height_tree(Tester *t, HeightTreeNode *expected, HeightTreeNode *got, const char *context) {
    if (!height_tree_eq(expected, got)) {
        const char* s_expected = height_tree_ascii(expected);
        const char* s_got = height_tree_ascii(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

char *rotations_to_str(Rotations rotations) {
    if (rotations == Left) {
        return "Left";
    } else if (rotations == DoubleRotationLeftRight) {
        return "DoubleRotationLeftRight";
    } else if (rotations == DoubleRotationRightLeft) {
        return "DoubleRotationRightLeft";
    } else {
        return "Right";
    }
}

void assert_rotations(Tester *t, Rotations expected, Rotations got, const char *context) {
    if (expected != got) {
        const char* s_expected = rotations_to_str(expected);
        const char* s_got = rotations_to_str(got);
        handle_assertion_failure(t, s_expected, s_got, context);
    }
}

typedef struct TestCase1_
{
    HeightTreeNode *before_rotation;
    HeightTreeNode *after_rotation;
} TestCase1;

char* render_exercise_1(TestCase1 test)
{
    String s = str_new();

    str_str(&s, "\nEingabebaum: \n");
    char *drawing = height_tree_ascii(test.before_rotation);
    str_str(&s, drawing);
    free(drawing);

    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 test) {
    char *args = render_exercise_1(test);

    HeightTreeNode *got_root = rotate_left(test.before_rotation);

    assert_height_tree(tester, test.after_rotation, got_root, args);

    free(args);
    height_tree_free(test.after_rotation);
    height_tree_free(got_root);
}

typedef struct TestCase2_
{
    HeightTreeNode *t;
    Rotations expected;
} TestCase2;

char* render_exercise_2(TestCase2 test)
{
    String s = str_new();

    str_str(&s, "\nEingabebaum: \n");
    char *drawing = height_tree_ascii(test.t);
    str_str(&s, drawing);
    free(drawing);

    return s.buf;
}

void do_test_2(Tester *tester, TestCase2 test) {
    char *args = render_exercise_2(test);

    Rotations got = determine_rotations(test.t);

    assert_rotations(tester, test.expected, got, args);

    free(args);
    height_tree_free(test.t);
}

HeightTreeNode *htn_9_7() {
    HeightTreeNode *t = height_tree_new_asdf(9, NULL);
    HeightTreeNode *l = height_tree_new_asdf(7, t);
    t->left = l;
    t->height = 2;
    return t;
}

HeightTreeNode *htn_7_9() {
    HeightTreeNode *t = height_tree_new_asdf(7, NULL);
    HeightTreeNode *r = height_tree_new_asdf(9, t);
    t->right = r;
    t->height = 2;
    return t;
}

HeightTreeNode *htn_tll() {
    HeightTreeNode *t = htn_9_7();
    HeightTreeNode *ll = height_tree_new_asdf(5, t->left);
    t->left->left = ll;
    t->left->height = 2;
    t->height = 3;
    return t;
}

HeightTreeNode *htn_ltr() {
    HeightTreeNode *t = htn_7_9();
    HeightTreeNode *l = height_tree_new_asdf(5, t);
    t->left = l;
    return t;
}

HeightTreeNode *htn_trr() {
    HeightTreeNode *t = height_tree_new_asdf(5, NULL);
    HeightTreeNode *r = height_tree_new_asdf(7, t);
    t->right = r;
    HeightTreeNode *rr = height_tree_new_asdf(9, r);
    t->right->right = rr;
    t->right->height = 2;
    t->height = 3;
    return t;
}

HeightTreeNode *htn_trrr() {
    HeightTreeNode *t = htn_trr();
    HeightTreeNode *rrr = height_tree_new_asdf(10, t->right->right);
    t->right->right->right = rrr;
    t->right->right->height = 2;
    t->right->height = 3;
    t->height = 4;
    return t;
}

HeightTreeNode *htn_tl_rr() {
    HeightTreeNode *t = htn_ltr();
    HeightTreeNode *rr = height_tree_new_asdf(10, t->right);
    t->right->right = rr;
    t->right->height = 2;
    t->height = 3;
    return t;
}

HeightTreeNode *htn_trrl() {
    HeightTreeNode *t = htn_trr();
    HeightTreeNode *rrl = height_tree_new_asdf(8, t->right->right);
    t->right->right->left = rrl;
    t->right->right->height = 2;
    t->right->height = 3;
    t->height = 4;
    return t;
}

HeightTreeNode *htn_tl_rl() {
    HeightTreeNode *t = htn_ltr();
    HeightTreeNode *rl = height_tree_new_asdf(8, t->right);
    t->right->left = rl;
    t->right->height = 2;
    t->height = 3;
    return t;
}

HeightTreeNode *htn_trlr() {
    HeightTreeNode *t = htn_trr();
    HeightTreeNode *rlr = height_tree_new_asdf(6, t->right);
    t->right->left = rlr;
    return t;
}

HeightTreeNode *htn_tlr_r() {
    HeightTreeNode *t = htn_ltr();
    HeightTreeNode *rlr = height_tree_new_asdf(6, t->left);
    t->left->right = rlr;
    t->height++;
    t->left->height++;
    return t;
}



int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");
    
    /* Aufgabe 1 */
    if (begin_exercise(&tester, "rotate_left", "Aufgabe 1: Linksrotation."))
    {
        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_7_9();
            test.after_rotation = htn_9_7();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_trr();
            test.after_rotation = htn_ltr();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_trrr();
            test.after_rotation = htn_tl_rr();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_trrl();
            test.after_rotation = htn_tl_rl();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_ltr();
            test.after_rotation = htn_tll();

            do_test_1(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase1 test;
            test.before_rotation = htn_trlr();
            test.after_rotation = htn_tlr_r();

            do_test_1(&tester, test);
        }
    }

    /* Aufgabe 2 */
    if (begin_exercise(&tester, "determine_rotations", "Aufgabe 2: Rotationsart bestimmen."))
    {
        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(3, test.t);
            test.t->left->left = height_tree_new_asdf(2, test.t->left);
            test.t->left->left->left = height_tree_new_asdf(1, test.t->left->left);
            test.t->left->right = height_tree_new_asdf(4, test.t->left);
            test.t->right = height_tree_new_asdf(8, test.t);

            test.t->left->left->height = 2;
            test.t->left->height = 3;
            test.t->height = 4;

            test.expected = Right;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(2, test.t);
            test.t->left->left = height_tree_new_asdf(1, test.t->left);
            test.t->left->right = height_tree_new_asdf(4, test.t->left);
            test.t->left->right->left = height_tree_new_asdf(3, test.t->left->right);
            test.t->right = height_tree_new_asdf(8, test.t);

            test.t->left->right->height = 2;
            test.t->left->height = 3;
            test.t->height = 4;

            test.expected = DoubleRotationLeftRight;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(2, test.t);
            test.t->left->left = height_tree_new_asdf(1, test.t->left);
            test.t->left->left->left = height_tree_new_asdf(0, test.t->left->left);
            test.t->left->right = height_tree_new_asdf(4, test.t->left);
            test.t->left->right->left = height_tree_new_asdf(3, test.t->left->right);
            test.t->right = height_tree_new_asdf(8, test.t);

            test.t->left->left->height = 2;
            test.t->left->right->height = 2;
            test.t->left->height = 3;
            test.t->height = 4;

            test.expected = Right;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->right = height_tree_new_asdf(7, test.t);
            test.t->right->right = height_tree_new_asdf(8, test.t->right);
            test.t->right->right->right = height_tree_new_asdf(9, test.t->right->right);
            test.t->right->left = height_tree_new_asdf(6, test.t->right);
            test.t->left = height_tree_new_asdf(2, test.t);

            test.t->right->right->height = 2;
            test.t->right->height = 3;
            test.t->height = 4;

            test.expected = Left;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->right = height_tree_new_asdf(8, test.t);
            test.t->right->right = height_tree_new_asdf(9, test.t->right);
            test.t->right->left = height_tree_new_asdf(6, test.t->right);
            test.t->right->left->right = height_tree_new_asdf(7, test.t->right->left);
            test.t->left = height_tree_new_asdf(2, test.t);

            test.t->right->left->height = 2;
            test.t->right->height = 3;
            test.t->height = 4;

            test.expected = DoubleRotationRightLeft;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(4, NULL);
            test.t->right = height_tree_new_asdf(7, test.t);
            test.t->right->right = height_tree_new_asdf(8, test.t->right);
            test.t->right->right->right = height_tree_new_asdf(9, test.t->right->right);
            test.t->right->left = height_tree_new_asdf(5, test.t->right);
            test.t->right->left->right = height_tree_new_asdf(6, test.t->right->left);
            test.t->left = height_tree_new_asdf(1, test.t);

            test.t->right->right->height = 2;
            test.t->right->left->height = 2;
            test.t->right->height = 3;
            test.t->height = 4;

            test.expected = Left;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(3, test.t);
            test.t->left->left = height_tree_new_asdf(2, test.t->left);

            test.t->left->height = 2;
            test.t->height = 3;

            test.expected = Right;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(2, test.t);
            test.t->left->right = height_tree_new_asdf(4, test.t->left);

            test.t->left->height = 2;
            test.t->height = 3;

            test.expected = DoubleRotationLeftRight;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->left = height_tree_new_asdf(2, test.t);
            test.t->left->left = height_tree_new_asdf(1, test.t->left);
            test.t->left->right = height_tree_new_asdf(4, test.t->left);

            test.t->left->height = 2;
            test.t->height = 3;

            test.expected = Right;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->right = height_tree_new_asdf(7, test.t);
            test.t->right->right = height_tree_new_asdf(8, test.t->right);

            test.t->right->height = 2;
            test.t->height = 3;

            test.expected = Left;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(5, NULL);
            test.t->right = height_tree_new_asdf(8, test.t);
            test.t->right->left = height_tree_new_asdf(6, test.t->right);

            test.t->right->height = 2;
            test.t->height = 3;

            test.expected = DoubleRotationRightLeft;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = height_tree_new_asdf(4, NULL);
            test.t->right = height_tree_new_asdf(7, test.t);
            test.t->right->right = height_tree_new_asdf(8, test.t->right);
            test.t->right->left = height_tree_new_asdf(5, test.t->right);

            test.t->right->height = 2;
            test.t->height = 3;

            test.expected = Left;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = htn_tll();
            test.expected = Right;

            do_test_2(&tester, test);
        }

        if (begin_testcase(&tester)) {
            TestCase2 test;
            test.t = htn_trr();
            test.expected = Left;

            do_test_2(&tester, test);
        }
    }


    return wrap_up(&tester);
}
