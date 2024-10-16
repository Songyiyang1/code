/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "02ex.c"
#include "testrunner.c"
#include "canvas.h"


#define TEST_NAME "02ex_test"

#define TESTS_1ABC 13
#define TESTS_2A 13
#define TESTS_2B 9
#define TESTS_2C 6
#define TESTS_LCM 13
#define TESTS_LCM_SUM 8

typedef struct Test1 {
    int n;
    int expected_both;
    int expected_or;
    int expected_either;
} exercises_1_data;

typedef struct Test2ab
{
    int x;
    int expected;
} exercises_2ab_data;

typedef struct Test2c
{
    int a;
    int b;
    int c;
    int result;
} exercise_2c_data;

typedef struct TestLCM
{
    int n;
    int expected;
} exercises_lcm_with_8_data;


static exercises_1_data exercises_1abc [TESTS_1ABC] = {
        { .n = 0, .expected_both = 0, .expected_or = 0, .expected_either = 0 },
        { .n = 6, .expected_both = 0, .expected_or = 0, .expected_either = 0 },
        { .n = 7, .expected_both = 0, .expected_or = 7, .expected_either = 7 },
        { .n = 9, .expected_both = 0, .expected_or = 7, .expected_either = 7 },
        { .n = 13, .expected_both = 0, .expected_or = 20, .expected_either = 20 },
        { .n = 14, .expected_both = 0, .expected_or = 34, .expected_either = 34 },
        { .n = 17, .expected_both = 0, .expected_or = 34, .expected_either = 34 },
        { .n = 65, .expected_both = 0, .expected_or = 510, .expected_either = 510 },
        { .n = 91, .expected_both = 91, .expected_or = 910, .expected_either = 819 },
        { .n = 100, .expected_both = 91, .expected_or = 1008, .expected_either = 917 },
        { .n = 200, .expected_both = 273, .expected_or = 4129, .expected_either = 3856 },
        { .n = 500, .expected_both = 1365, .expected_or = 26160, .expected_either = 24795 },
        { .n = 12345, .expected_both = 835380, .expected_or = 15909457, .expected_either = 15074077 },
};

static exercises_2ab_data exercise_2a[TESTS_2A] = {
        { .x = 1, .expected = 1 },
        { .x = 0, .expected = 0 },
        { .x = -1, .expected = -1 },
        { .x = 13, .expected = 1 },
        { .x = 57, .expected = 1 },
        { .x = -45, .expected = -1 },
        { .x = -633, .expected = -1 },
        { .x = 12345, .expected = 1 },
        { .x = 135163, .expected = 1 },
        { .x = -12345, .expected = -1 },
        { .x = -432462, .expected = -1 },
        { .x = 2147483647, .expected = 1 },
        { .x = -2147483648, .expected = -1 },
};
static exercises_2ab_data exercise_2b[TESTS_2B] = {
        {.x = -1, .expected = 0},
        {.x = 0, .expected = 1},
        {.x = 1, .expected = 0},
        {.x = 4, .expected = 1},
        {.x = 5, .expected = 0},
        {.x = 200, .expected = 0},
        {.x = 1600, .expected = 1},
        {.x = 2023, .expected = 0},
        {.x = 2024, .expected = 1},
};
static exercise_2c_data exercise_2c [TESTS_2C] = {
        { .a = 0, .b = 7, .c = 3, .result = 7 },
        { .a = 1, .b = 2, .c = 3, .result = 3 },
        { .a = 0, .b = 0, .c = 0, .result = 0 },
        { .a = 178, .b = 112, .c = 245, .result = 245 },
        { .a = 100, .b = 10, .c = 1, .result = 100 },
        { .a = 3, .b = 9, .c = 6, .result = 9 },
};

static exercises_lcm_with_8_data exercise_lcm [TESTS_LCM] = {
        {.n = 1, .expected = 8},
        {.n = 2, .expected = 8},
        {.n = 3, .expected = 24},
        {.n = 10, .expected = 40},
        {.n = 5, .expected = 40},
        {.n = 20, .expected = 40},
        {.n = 8, .expected = 8},
        {.n = 6, .expected = 24},
        {.n = 4, .expected = 8},
        {.n = 12, .expected = 24},
        {.n = 16, .expected = 16},
        {.n = 9, .expected = 72},
        {.n = 13, .expected = 104},
};

static exercises_lcm_with_8_data exercise_lcm_sum [TESTS_LCM_SUM] = {
        {.n = 1, .expected = 8},
        {.n = 2, .expected = 16},
        {.n = 3, .expected = 40},
        {.n = 6, .expected = 112},
        {.n = 10, .expected = 288},
        {.n = 32, .expected = 2768},
        {.n = 99, .expected = 26776},
        {.n = 160, .expected = 68880},
};

char* render_exercises_1abc(exercises_1_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}
char* render_exercise_2a(exercises_2ab_data testcase)
{
    const char *x = format_int(testcase.x);
    int len = strlen("x = ") + strlen(x) + 1;
    char *str = malloc(len);
    snprintf(str, len, "x = %s", x);
    free((char*) x);
    return str;
}
char* render_exercise_2b(exercises_2ab_data testcase)
{
    const char *year = format_int(testcase.x);
    int len = strlen("year = ") + strlen(year) + 1;
    char *str = malloc(len);
    snprintf(str, len, "year = %s", year);
    free((char*) year);
    return str;
}
char* render_exercise_2c(exercise_2c_data testcase)
{
    const char *a = format_int(testcase.a);
    const char *b = format_int(testcase.b);
    const char *c = format_int(testcase.c);
    int len = strlen("a = ") + strlen(a) + strlen(", b = ") + strlen(b) + strlen(" und c = ") + strlen(c) + 1;
    char *str = malloc(len);
    snprintf(str, len, "a = %s, b = %s und c = %s", a, b, c);
    free((char*) a);
    free((char*) b);
    free((char*) c);
    return str;
}

char* render_exercises_lcm_with_8(exercises_lcm_with_8_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

int main(int argc, char const *argv[])
{
    Tester tester = tester_new(argc-1,argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");
    /* Aufgabe 1a */
    if(begin_exercise(&tester, "sum_divisible_both", "Aufgabe 1a: Summe der Vielfachen von 7 *und* 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_both, sum_divisible_both(exercises_1abc[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester, "sum_divisible_or", "Aufgabe 1b: Summe der Vielfachen von 7 *oder* 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_or, sum_divisible_or(exercises_1abc[i].n), args);
                free(args);
            }
        }
    }
    /* Aufgabe 1c */
    if(begin_exercise(&tester, "sum_divisible_either", "Aufgabe 1c: Summe der Vielfachen von *entweder* 7 oder 13."))
    {
        for (int i = 0; i < TESTS_1ABC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_1abc(exercises_1abc[i]);
                assert_uint(&tester, exercises_1abc[i].expected_either, sum_divisible_either(exercises_1abc[i].n),
                            args);
                free(args);
            }
        }
    }
    /* Aufgabe 2a*/
    if(begin_exercise(&tester, "signum", "Aufgabe 2a: Vorzeichenbestimmung ganzer Zahlen mit signum."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2a(exercise_2a[i]);
                assert_int(&tester, exercise_2a[i].expected, signum(exercise_2a[i].x), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b*/
    if(begin_exercise(&tester, "is_leapyear", "Aufgabe 2b: Berechnung von Schaltjahren."))
    {
        for (int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2b(exercise_2b[i]);
                assert_int(&tester, exercise_2b[i].expected, is_leapyear(exercise_2b[i].x), args);
                free(args);
            }
        }
    }
     /* Aufgabe 2c */
     if(begin_exercise(&tester, "greatest_of_three", "Aufgabe 2c: Vergleichen und heraussuchen des größten Werts."))
     {
         for (int i = 0; i < TESTS_2C; i++)
         {
             if(begin_testcase(&tester))
             {
                 if (tester.successful)
                 {
                     char *args = render_exercise_2c(exercise_2c[i]);
                     int compiled_res = greatest_of_three(exercise_2c[i].a, exercise_2c[i].b, exercise_2c[i].c);
                     assert_int(&tester, exercise_2c[i].result, compiled_res, args);
                     free(args);
                 }
             }
         }
     }
    
    /* Least common multiple with 8 */
    if(begin_exercise(&tester,"least_common_multiple_with_8","Aufgabe 3a: Kleinste gemeinsame Vielfache mit 8 finden."))
    {
        for (int i = 0; i < TESTS_LCM; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_lcm_with_8(exercise_lcm[i]);
                assert_int(&tester, exercise_lcm[i].expected, least_common_multiple_with_8(exercise_lcm[i].n), args);
                free(args);
            }
        }
    }
    /* Sum of least common multiples with 8 */
    if(begin_exercise(&tester,"sum_least_common_multiples_with_8", "Aufgabe 3b: Alle kleinsten gemeinsamen Vielfachen bis n summieren."))
    {
        for (int i = 0; i < TESTS_LCM_SUM; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_lcm_with_8(exercise_lcm_sum[i]);
                assert_int(&tester, exercise_lcm_sum[i].expected,
                           sum_least_common_multiples_with_8(exercise_lcm_sum[i].n), args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}