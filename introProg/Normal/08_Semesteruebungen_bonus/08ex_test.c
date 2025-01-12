/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "08ex.c"
#include "testrunner.c"
#include "String.h"

#define TEST_NAME "08ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_1 3
#define TEST_CASES_2 5

void render_array_with_length(String *s, ArrayWithLength arr) {
    str_u16s(s, arr.arr, arr.len);
}

void assert_array_with_length(Tester *t, ArrayWithLength expected, ArrayWithLength got, const char *context) {
    if (expected.len != got.len || !uint16_array_equality(expected.arr, got.arr, expected.len)) {
        String s_exp = str_new();
        render_array_with_length(&s_exp, expected);
        String s_got = str_new();
        render_array_with_length(&s_got, got);
        
        handle_assertion_failure(t, s_exp.buf, s_got.buf, context);

        str_free(s_exp);
        str_free(s_got);
    }
}

ArrayWithLength copy_array_with_length(ArrayWithLength arr) {
    ArrayWithLength ret;
    ret.arr = copy_u16s(arr.arr, arr.len);
    ret.len = arr.len;
    return ret;
}

typedef struct TestCase2_ {
    ArrayWithLength arr1;
    ArrayWithLength arr2;
    ArrayWithLength expected;
} TestCase2;

typedef struct TestCase3_ {
    ArrayWithLength *arrs;
    size_t count;
    ArrayWithLength expected;
} TestCase3;

char* render_exercise_1(ArrayWithLength arr)
{
    String s = str_new();
    render_array_with_length(&s, arr);
    return s.buf;
}

char* render_exercise_2(TestCase2 test)
{
    String s = str_new();

    str_str(&s, "\nArray 1: ");
    render_array_with_length(&s, test.arr1);
    str_str(&s, "\nArray 2: ");
    render_array_with_length(&s, test.arr2);
    str_str(&s, "\n");

    return s.buf;
}

char* render_exercise_3(TestCase3 test)
{
    String s = str_new();
    str_str(&s, "\nArrays (count = ");
    str_uint(&s, test.count);
    str_str(&s, "):");

    for (size_t i = 0; i < test.count; i++) {
        str_str(&s, "\n  ");
        str_u16s(&s, test.arrs[i].arr, test.arrs[i].len);
    }

    return s.buf;
}

void do_test_1(Tester *tester, ArrayWithLength arr) {
    ArrayWithLength copy = copy_array_with_length(arr);
    ArrayWithLength got = base_case(copy);

    char *args = render_exercise_1(arr);
    assert_array_with_length(tester, arr, got, args);

    free(args);
    free(got.arr);
    free(copy.arr);
    free(arr.arr);
}

void do_test_2(Tester *tester, TestCase2 test) {
    ArrayWithLength copy1 = copy_array_with_length(test.arr1);
    ArrayWithLength copy2 = copy_array_with_length(test.arr2);
    ArrayWithLength got = combine(copy1, copy2);

    char *args = render_exercise_2(test);
    assert_array_with_length(tester, test.expected, got, args);

    free(args);
    free(got.arr);
    free(copy1.arr);
    free(copy2.arr);
    free(test.arr1.arr);
    free(test.arr2.arr);
    free(test.expected.arr);
}

void do_test_3(Tester *tester, TestCase3 test) {
    ArrayWithLength *copy = malloc(sizeof(ArrayWithLength) * test.count);
    for (size_t i = 0; i < test.count; i++) {
        copy[i] = copy_array_with_length(test.arrs[i]);
    }

    ArrayWithLength got = merge_k(copy, test.count);

    char *args = render_exercise_3(test);
    assert_array_with_length(tester, test.expected, got, args);

    free(args);
    free(got.arr);
    for (size_t i = 0; i < test.count; i++)
    {
        free(copy[i].arr);
        free(test.arrs[i].arr);
    }
    
    free(copy);
    free(test.arrs);
    free(test.expected.arr);
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "base_case", "Aufgabe 1: Der Rekursionsanker."))
    {
        if(begin_testcase(&tester)) {
            ArrayWithLength input;
            input.arr = malloc(sizeof(uint16_t));
            input.arr[0] = 17;
            input.len = 0;
            
            do_test_1(&tester, input);
        }

        if(begin_testcase(&tester)) {
            ArrayWithLength input;
            input.arr = malloc(0);
            input.len = 0;
            
            do_test_1(&tester, input);
        }

        if(begin_testcase(&tester)) {
            ArrayWithLength input;
            input.arr = malloc(sizeof(uint16_t) * 3);
            input.arr[0] = 9;
            input.arr[1] = 9;
            input.arr[2] = 4;
            input.len = 3;
            
            do_test_1(&tester, input);
        }
    }
    
    /* Aufgabe 2 */
    if (begin_exercise(&tester, "combine", "Aufgabe 2: Zwei Teillösungen kombinieren."))
    {
        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
            tc.arr1.len = 0;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
            tc.arr2.len = 0;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
            tc.expected.len = 0;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
            tc.arr1.len = 0;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr2.arr[0] = 5;
            tc.arr2.len = 1;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.expected.arr[0] = 5;
            tc.expected.len = 1;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr1.arr[0] = 7;
            tc.arr1.len = 1;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
            tc.arr2.len = 0;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.expected.arr[0] = 7;
            tc.expected.len = 1;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr1.arr[0] = 7;
            tc.arr1.len = 1;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr2.arr[0] = 5;
            tc.arr2.len = 1;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
            tc.expected.arr[0] = 7;
            tc.expected.arr[1] = 5;
            tc.expected.len = 2;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr1.arr[0] = 2;
            tc.arr1.len = 1;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr2.arr[0] = 8;
            tc.arr2.len = 1;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
            tc.expected.arr[0] = 8;
            tc.expected.arr[1] = 2;
            tc.expected.len = 2;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr1.arr[0] = 3;
            tc.arr1.len = 1;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
            tc.arr2.arr[0] = 3;
            tc.arr2.len = 1;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
            tc.expected.arr[0] = 3;
            tc.expected.arr[1] = 3;
            tc.expected.len = 2;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 5);
            tc.arr1.arr[0] = 1;
            tc.arr1.arr[1] = 1;
            tc.arr1.arr[2] = 1;
            tc.arr1.arr[3] = 1;
            tc.arr1.arr[4] = 1;
            tc.arr1.len = 5;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
            tc.arr2.arr[0] = 1;
            tc.arr2.arr[1] = 1;
            tc.arr2.len = 2;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 7);
            tc.expected.arr[0] = 1;
            tc.expected.arr[1] = 1;
            tc.expected.arr[2] = 1;
            tc.expected.arr[3] = 1;
            tc.expected.arr[4] = 1;
            tc.expected.arr[5] = 1;
            tc.expected.arr[6] = 1;
            tc.expected.len = 7;

            do_test_2(&tester, tc);
        }

        if (begin_testcase(&tester)) {
            TestCase2 tc;
            tc.arr1.arr = (uint16_t *) malloc(sizeof(uint16_t) * 3);
            tc.arr1.arr[0] = 8;
            tc.arr1.arr[1] = 8;
            tc.arr1.arr[2] = 2;
            tc.arr1.len = 3;
            tc.arr2.arr = (uint16_t *) malloc(sizeof(uint16_t) * 4);
            tc.arr2.arr[0] = 9;
            tc.arr2.arr[1] = 8;
            tc.arr2.arr[2] = 4;
            tc.arr2.arr[3] = 1;
            tc.arr2.len = 4;
            
            tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 7);
            tc.expected.arr[0] = 9;
            tc.expected.arr[1] = 8;
            tc.expected.arr[2] = 8;
            tc.expected.arr[3] = 8;
            tc.expected.arr[4] = 4;
            tc.expected.arr[5] = 2;
            tc.expected.arr[6] = 1;
            tc.expected.len = 7;

            do_test_2(&tester, tc);
        }
    }

    /* Aufgabe 3 */
    if (begin_exercise(&tester, "merge_k", "Aufgabe 3: Teilen und herrschen und so."))
        {
            if (begin_testcase(&tester)) {
                TestCase3 tc;
                tc.count = 1;
                tc.arrs = (ArrayWithLength *) malloc(sizeof(ArrayWithLength) * 1);

                tc.arrs[0].arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
                tc.arrs[0].arr[0] = 8;
                tc.arrs[0].arr[1] = 7;
                tc.arrs[0].len = 2;

                tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 2);
                tc.expected.arr[0] = 8;
                tc.expected.arr[1] = 7;
                tc.expected.len = 2;

                do_test_3(&tester, tc);
            }

            if (begin_testcase(&tester)) {
                TestCase3 tc;
                tc.count = 3;
                tc.arrs = (ArrayWithLength *) malloc(sizeof(ArrayWithLength) * 3);

                tc.arrs[0].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[0].arr[0] = 0;
                tc.arrs[0].len = 1;
                tc.arrs[1].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[1].arr[0] = 1;
                tc.arrs[1].len = 1;
                tc.arrs[2].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[2].arr[0] = 2;
                tc.arrs[2].len = 1;

                tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 3);
                tc.expected.arr[0] = 2;
                tc.expected.arr[1] = 1;
                tc.expected.arr[2] = 0;
                tc.expected.len = 3;

                do_test_3(&tester, tc);
            }

            if (begin_testcase(&tester)) {
                TestCase3 tc;
                tc.count = 4;
                tc.arrs = (ArrayWithLength *) malloc(sizeof(ArrayWithLength) * 4);

                tc.arrs[0].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[0].arr[0] = 0;
                tc.arrs[0].len = 1;
                tc.arrs[1].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[1].arr[0] = 1;
                tc.arrs[1].len = 1;
                tc.arrs[2].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[2].arr[0] = 2;
                tc.arrs[2].len = 1;
                tc.arrs[3].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[3].arr[0] = 3;
                tc.arrs[3].len = 1;

                tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 4);
                tc.expected.arr[0] = 3;
                tc.expected.arr[1] = 2;
                tc.expected.arr[2] = 1;
                tc.expected.arr[3] = 0;
                tc.expected.len = 4;

                do_test_3(&tester, tc);
            }

            if (begin_testcase(&tester)) {
                TestCase3 tc;
                tc.count = 5;
                tc.arrs = (ArrayWithLength *) malloc(sizeof(ArrayWithLength) * 5);

                tc.arrs[0].arr = (uint16_t *) malloc(sizeof(uint16_t) * 3);
                tc.arrs[0].arr[0] = 8;
                tc.arrs[0].arr[1] = 8;
                tc.arrs[0].arr[2] = 2;
                tc.arrs[0].len = 3;
                tc.arrs[1].arr = (uint16_t *) malloc(sizeof(uint16_t) * 4);
                tc.arrs[1].arr[0] = 9;
                tc.arrs[1].arr[1] = 8;
                tc.arrs[1].arr[2] = 4;
                tc.arrs[1].arr[3] = 1;
                tc.arrs[1].len = 4;
                tc.arrs[2].arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
                tc.arrs[2].len = 0;
                tc.arrs[3].arr = (uint16_t *) malloc(sizeof(uint16_t) * 3);
                tc.arrs[3].arr[0] = 8;
                tc.arrs[3].arr[1] = 8;
                tc.arrs[3].arr[2] = 2;
                tc.arrs[3].len = 3;
                tc.arrs[4].arr = (uint16_t *) malloc(sizeof(uint16_t) * 1);
                tc.arrs[4].arr[0] = 8;
                tc.arrs[4].len = 1;

                tc.expected.arr = (uint16_t *) malloc(sizeof(uint16_t) * 11);
                tc.expected.arr[0] = 9;
                tc.expected.arr[1] = 8;
                tc.expected.arr[2] = 8;
                tc.expected.arr[3] = 8;
                tc.expected.arr[4] = 8;
                tc.expected.arr[5] = 8;
                tc.expected.arr[6] = 8;
                tc.expected.arr[7] = 4;
                tc.expected.arr[8] = 2;
                tc.expected.arr[9] = 2;
                tc.expected.arr[10] = 1;
                tc.expected.len = 11;

                do_test_3(&tester, tc);
            }

        }

    return wrap_up(&tester);
}
