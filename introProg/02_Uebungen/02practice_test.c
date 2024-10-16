/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "02practice.c"
#include "testrunner.c"

#define TEST_NAME "02practice_test"
#define TESTS_3A 17
#define TESTS_3B 13
#define TESTS_POWERS 9

typedef struct Test3
{
    int n;
    int expected;
} exercises_3_data;

typedef struct TestPowers
{
    int n;
    int expected;
} exercise_powers_data;

static exercises_3_data exercise_3a[TESTS_3A] = {
        { .n = 0, .expected = 0 },
        { .n = 2, .expected = 1 },
        { .n = 1, .expected = 0 },
        { .n = 55, .expected = 0 },
        { .n = 10, .expected = 0 },
        { .n = 23, .expected = 1 },
        { .n = 3, .expected = 1 },
        { .n = 121, .expected = 0 },
        { .n = 777, .expected = 0 },
        { .n = 443, .expected = 1 },
        { .n = 42, .expected = 0 },
        { .n = 79, .expected = 1 },
        { .n = 1008, .expected = 0 },
        { .n = 1009, .expected = 1 },
        { .n = 9649, .expected = 1 },
        { .n = 2023, .expected = 0 },
        { .n = 17, .expected = 1 },
};
static exercises_3_data exercise_3b[TESTS_3B] = {
        { .n = 1, .expected = 2 },
        { .n = 4, .expected = 17 },
        { .n = 0, .expected = 0 },
        { .n = 10, .expected = 129 },
        { .n = 17, .expected = 440 },
        { .n = 16, .expected = 381 },
        { .n = 3, .expected = 10 },
        { .n = 6, .expected = 41 },
        { .n = 9, .expected = 100 },
        { .n = 25, .expected = 1060 },
        { .n = 42, .expected = 3447 },
        { .n = 7, .expected = 58 },
        { .n = 1024, .expected = 3875933 },
};

static exercise_powers_data exercise_powers[TESTS_POWERS] = {
        { .n = 1, .expected = 2 },
        { .n = 4, .expected = 341 },
        { .n = 0, .expected = 1 },
        { .n = 3, .expected = 40 },
        { .n = 9, .expected = 435848050 },
        { .n = 8, .expected = 19173961 },
        { .n = 5, .expected = 3906 },
        { .n = 7, .expected = 960800 },
        { .n = 2, .expected = 7 },
};

char* render_exercises_3abc(exercises_3_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

char* render_exercise_powers(exercise_powers_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 3a */
    if(begin_exercise(&tester, "is_prime", "Zurückgeben ob eine Zahl eine Primzahl ist oder nicht."))
    {
        for (int i = 0; i < TESTS_3A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_3abc(exercise_3a[i]);
                assert_int(&tester, exercise_3a[i].expected, is_prime(exercise_3a[i].n), args);
                free(args);
            }
        }
    }

    /* Aufgabe 3b */
    if(begin_exercise(&tester, "sum_first_primes", "Summe der ersten n Primzahlen ausrechnen."))
    {
        for (int i = 0; i < TESTS_3B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_3abc(exercise_3b[i]);
                assert_int(&tester, exercise_3b[i].expected, sum_first_primes(exercise_3b[i].n), args);
                free(args);
            }
        }
    }

    /* Sum First Powers */
    if(begin_exercise(&tester, "sum_first_powers", "Die Potenzen von n bis zur einschließlich n-ten Potenz summieren."))
    {
        for (int i = 0; i < TESTS_POWERS; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_powers(exercise_powers[i]);
                assert_int(&tester, exercise_powers[i].expected, sum_first_powers(exercise_powers[i].n), args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}