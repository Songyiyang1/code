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
    size_t first_one;
} TestCase1;

char* render_exercise_1(TestCase1 testcase)
{
    String s = str_new();
    str_str(&s, "Array der Sphinx: ");
    str_u16s(&s, testcase.arr, testcase.len);
    return s.buf;
}

void do_test_1(Tester *tester, TestCase1 testcase) {
    Sphinx s = new_sphinx(testcase.arr, testcase.len, ceil(log2(testcase.len)) + 1);
    size_t got = zero_one_sphinx(&s, testcase.len);

    char *args = render_exercise_1(testcase);
    assert_size(tester, testcase.first_one, got, args);
    free(args);

    free(testcase.arr);
    free_sphinx(s);
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if (begin_exercise(&tester, "zero_one_sphinx", "Aufgabe 1: Die erste Eins finden."))
    {
        for (size_t len = 0; len < 32; len++) {
            for (size_t first_one = 0; first_one <= len; first_one++) {
                if(begin_testcase(&tester)) {
                    TestCase1 tc;
                    tc.len = len;
                    tc.arr = malloc(sizeof(uint16_t) * len);
                    for (size_t i = 0; i < len; i++) {
                        if (i < first_one) {
                            tc.arr[i] = 0;
                        } else {
                            tc.arr[i] = 1;
                        }
                    }
                    tc.first_one = first_one;
                    do_test_1(&tester, tc);
                }
            }
        }

    }

    return wrap_up(&tester);
}
