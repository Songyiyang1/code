/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "08ex.c"
#include "testrunner.c"
#include "String.h"
#include "sphinximpl.h"

#define TEST_NAME "08ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_1 3
#define TEST_CASES_2 5

typedef struct TestCase1_ {
    size_t len;
    uint16_t *arr;
    bool has_needle;
} TestCase1;

char* render_exercise_1(TestCase1 testcase)
{
    String s = str_new();
    str_str(&s, "Array der Sphinx: ");
    str_u16s(&s, testcase.arr, testcase.len);
    // const char *arr_fmt = format_uint16_array(testcase.arr, testcase.len);
    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 testcase) {
    Sphinx s = new_sphinx(testcase.arr, testcase.len, ceil(log2(testcase.len)) + 1);
    bool got = descending_sphinx(&s, testcase.len);

    char *args = render_exercise_1(testcase);
    assert_bool(tester, testcase.has_needle, got, args);
    free(args);

    free(testcase.arr);
    free_sphinx(s);
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "descending_sphinx", "Aufgabe 1: In absteigendem Array suchen."))
    {
        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 8;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.arr[0] = 15100;
            tc.arr[1] = 14544;
            tc.arr[2] = 12345;
            tc.arr[3] = 10421;
            tc.arr[4] = 7337;
            tc.arr[5] = 632;
            tc.arr[6] = 95;
            tc.arr[7] = 3;
            tc.has_needle = true;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 8;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.arr[0] = 15100;
            tc.arr[1] = 14544;
            tc.arr[2] = 10422;
            tc.arr[3] = 10421;
            tc.arr[4] = 7337;
            tc.arr[5] = 632;
            tc.arr[6] = 95;
            tc.arr[7] = 3;
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 0;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 1;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.arr[0] = 12345;
            tc.has_needle = true;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 1;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.arr[0] = 1234;
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 1;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            tc.arr[0] = 14531;
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 13;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            for (size_t j = 0; j < 13; j++) {
                    tc.arr[j] = 0;
            }
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 13;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            for (size_t j = 0; j < 13; j++) {
                    tc.arr[j] = 16262;
            }
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        
        for (size_t i = 0; i < 13; i++) {
            if(begin_testcase(&tester)) {
                TestCase1 tc;
                tc.len = 13;
                tc.arr = malloc(sizeof(uint16_t) * tc.len);
                for (size_t j = 0; j < 13; j++) {
                    if (j < i) {
                        tc.arr[j] = 14111;
                    } else if (j > i) {
                        tc.arr[j] = 57;
                    } else {
                        tc.arr[j] = 12345;
                    }
                }
                tc.has_needle = true;
                do_test_1(&tester, tc);
            }
        }

        if(begin_testcase(&tester)) {
            TestCase1 tc;
            tc.len = 161;
            tc.arr = malloc(sizeof(uint16_t) * tc.len);
            for (size_t j = 0; j < 161; j++) {
                    tc.arr[j] = 0;
            }
            tc.has_needle = false;
            do_test_1(&tester, tc);
        }

        for (size_t i = 0; i < 161; i++) {
            if(begin_testcase(&tester)) {
                TestCase1 tc;
                tc.len = 161;
                tc.arr = malloc(sizeof(uint16_t) * tc.len);
                for (size_t j = 0; j < 161; j++) {
                    if (j < i) {
                        tc.arr[j] = 14111;
                    } else if (j > i) {
                        tc.arr[j] = 57;
                    } else {
                        tc.arr[j] = 12345;
                    }
                }
                tc.has_needle = true;
                do_test_1(&tester, tc);
            }
        }
    }

    return wrap_up(&tester);
}
