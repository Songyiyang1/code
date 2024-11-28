/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "10ex.c"
#include "testrunner.c"

#define TEST_NAME "10ex_test"

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1 */
    if(begin_exercise(&tester,"return_five","Aufgabe 1: Die Zahl zwischen vier und sechs berechnen."))
    {
        if(begin_testcase(&tester)) {
            int got = return_five();
            assert_uint(&tester, 5, got, "");
        }
    }

    return wrap_up(&tester);
}
