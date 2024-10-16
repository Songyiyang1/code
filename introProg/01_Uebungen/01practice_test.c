/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "01practice.c"
#include "testrunner.c"

#define TEST_NAME "01practice_test"
#define TESTS_BAKERY 13
#define TESTS_UNITS 16
#define TESTS_ROOT 13
#define TESTS_SUM 11
#define TESTS_REVERSE 10

typedef struct TestBakery
{
    int cupcakes;
    int pies;
    int cakes;
    int expected_price;
} exercise_bakery_data;

typedef struct TestTime
{
    int input_in_seconds;
    int expected_hours;
    int expected_minutes;
    int expected_seconds;
} exercise_units_data;

typedef struct TestsRootDigits
{
    int n;
    int expected_bool;
    int result;
} exercises_root_digits_data;

static exercise_bakery_data exercise_bakery [TESTS_BAKERY] = {
        {.cupcakes = 1, .pies = 0, .cakes = 0, .expected_price = 2},
        {.cupcakes = 0, .pies = 1, .cakes = 0, .expected_price = 3},
        {.cupcakes = 0, .pies = 0, .cakes = 1, .expected_price = 4},
        {.cupcakes = 0, .pies = 0, .cakes = 0, .expected_price = 0},
        {.cupcakes = 1, .pies = 1, .cakes = 1, .expected_price = 9},
        {.cupcakes = 1, .pies = 2, .cakes = 0, .expected_price = 8},
        {.cupcakes = 3, .pies = 2, .cakes = 1, .expected_price = 16},
        {.cupcakes = 10, .pies = 0, .cakes = 0, .expected_price = 16},
        {.cupcakes = 0, .pies = 10, .cakes = 0, .expected_price = 24},
        {.cupcakes = 0, .pies = 0, .cakes = 10, .expected_price = 32},
        {.cupcakes = 5, .pies = 5, .cakes = 5, .expected_price = 36},
        {.cupcakes = 4, .pies = 3, .cakes = 2, .expected_price = 20},
        {.cupcakes = 32, .pies = 45, .cakes = 91, .expected_price = 450},
};
static exercise_units_data exercise_units [TESTS_UNITS] = {
        {.input_in_seconds = 1, .expected_hours = 0, .expected_minutes = 0, .expected_seconds = 1},
        {.input_in_seconds = 60, .expected_hours = 0, .expected_minutes = 1, .expected_seconds = 0},
        {.input_in_seconds = 3600, .expected_hours = 1, .expected_minutes = 0, .expected_seconds = 0},
        {.input_in_seconds = 0, .expected_hours = 0, .expected_minutes = 0, .expected_seconds = 0},
        {.input_in_seconds = 17, .expected_hours = 0, .expected_minutes = 0, .expected_seconds = 17},
        {.input_in_seconds = 1634, .expected_hours = 0, .expected_minutes = 27, .expected_seconds = 14},
        {.input_in_seconds = 144, .expected_hours = 0, .expected_minutes = 2, .expected_seconds = 24},
        {.input_in_seconds = 7434, .expected_hours = 2, .expected_minutes = 3, .expected_seconds = 54},
        {.input_in_seconds = 645, .expected_hours = 0, .expected_minutes = 10, .expected_seconds = 45},
        {.input_in_seconds = 121, .expected_hours = 0, .expected_minutes = 2, .expected_seconds = 1},
        {.input_in_seconds = 8, .expected_hours = 0, .expected_minutes = 0, .expected_seconds = 8},
        {.input_in_seconds = 85, .expected_hours = 0, .expected_minutes = 1, .expected_seconds = 25},
        {.input_in_seconds = 976, .expected_hours = 0, .expected_minutes = 16, .expected_seconds = 16},
        {.input_in_seconds = 263, .expected_hours = 0, .expected_minutes = 4, .expected_seconds = 23},
        {.input_in_seconds = 3663, .expected_hours = 1, .expected_minutes = 1, .expected_seconds = 3},
        {.input_in_seconds = 1024, .expected_hours = 0, .expected_minutes = 17, .expected_seconds = 4},
};
static exercises_root_digits_data exercise_root [TESTS_ROOT] = {
        {.n = 1, .expected_bool = 1},
        {.n = 9, .expected_bool = 1},
        {.n = 0, .expected_bool = 1},
        {.n = 11, .expected_bool = 0},
        {.n = 32, .expected_bool = 0},
        {.n = 36, .expected_bool = 1},
        {.n = 2, .expected_bool = 0},
        {.n = 64, .expected_bool = 1},
        {.n = 100, .expected_bool = 1},
        {.n = 71, .expected_bool = 0},
        {.n = 144, .expected_bool = 1},
        {.n = 42, .expected_bool = 0},
        {.n = 256, .expected_bool = 1},
};

static exercises_root_digits_data exercise_sum [TESTS_SUM] = {
        { .n = 1234, .result = 10 },
        { .n = 23, .result = 5 },
        { .n = 777, .result = 21 },
        { .n = 512, .result = 8 },
        { .n = 0, .result = 0 },
        { .n = 7698, .result = 30 },
        { .n = 371, .result = 11 },
        { .n = 2023, .result = 7 },
        { .n = 11, .result = 2 },
        { .n = 9392911, .result = 34 },
        { .n = 123456789, .result = 45 },
};
static exercises_root_digits_data exercise_reverse [TESTS_REVERSE] = {
        { .n = 1234, .result = 4321 },
        { .n = 10, .result = 1 },
        { .n = 2, .result = 2 },
        { .n = 0, .result = 0 },
        { .n = 49, .result = 94 },
        { .n = 9999, .result = 9999 },
        { .n = 910632, .result = 236019 },
        { .n = 1000, .result = 1 },
        { .n = 2023, .result = 3202 },
        { .n = 8941722, .result = 2271498 },
};

char* render_exercise_bakery(exercise_bakery_data testcase)
{
    const char *cupcake = format_int(testcase.cupcakes);
    const char *pie = format_int(testcase.pies);
    const char *cake = format_int(testcase.cakes);
    int len = strlen("Wir wollen ") + strlen(cupcake) + strlen(" Muffin(s), ") + strlen(pie) + strlen(" Kuchen und ")
            + strlen(cake) + strlen(" Torte(n) kaufen.") + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir wollen %s Muffin(s), %s Kuchen und %s Torte(n) kaufen.", cupcake, pie, cake);
    free((char*) cupcake);
    free((char*) pie);
    free((char*) cake);
    return str;
}
char* render_exercise_units(exercise_units_data testcase, int hours, int minutes, int seconds)
{
    const char *input = format_int(testcase.input_in_seconds);
    const char *exp_hours = format_int(testcase.expected_hours);
    const char *exp_minutes = format_int(testcase.expected_minutes);
    const char *exp_seconds = format_int(testcase.expected_seconds);
    const char *got_hours = format_int(hours);
    const char *got_minutes = format_int(minutes);
    const char *got_seconds = format_int(seconds);
    int len = strlen("Die Zeit in Sekunden ist: ") + strlen(input) + strlen("\n\n" TESTRUNNER_LABEL "Erwartet:\n") +
            strlen( TESTRUNNER_LABEL " Stunden ") + strlen(exp_hours) + strlen(" Minuten ") + strlen(exp_minutes)
                    + strlen(" und  Sekunden") + strlen(exp_seconds) + strlen("\n\n" TESTRUNNER_LABEL "Erhielt:\n")
                    + strlen( TESTRUNNER_LABEL " Stunden ") + strlen(got_hours) + strlen(" Minuten ") + strlen(got_minutes)
                    + strlen(" und  Sekunden ") + strlen(got_seconds) + strlen("\n\n" TESTRUNNER_LABEL "Internes Ergebnis:") + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Die Zeit in Sekunden ist: %s\n\n" TESTRUNNER_LABEL "Erwartet:\n"
    TESTRUNNER_LABEL "%s Stunden %s Minuten und %s Sekunden\n\n" TESTRUNNER_LABEL "Erhielt:\n" TESTRUNNER_LABEL
    "%s Stunden %s Minuten und %s Sekunden\n\n" TESTRUNNER_LABEL "Internes Ergebnis:", input, exp_hours,
    exp_minutes, exp_seconds, got_hours, got_minutes, got_seconds);
    free((char*) input);
    free((char*) exp_hours);
    free((char*) exp_minutes);
    free((char*) exp_seconds);
    free((char*) got_hours);
    free((char*) got_minutes);
    free((char*) got_seconds);
    return str;
}
char* render_exercises_root_sum_reverse(exercises_root_digits_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Bakery */
    if(begin_exercise(&tester,"bakery","Den Gesamtpreis von Backwaren errechnen."))
    {
        for (int i = 0; i < TESTS_BAKERY; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_bakery(exercise_bakery[i]);
                assert_int(&tester, exercise_bakery[i].expected_price, bakery(exercise_bakery[i].cupcakes,
                                                                                   exercise_bakery[i].pies,
                                                                                   exercise_bakery[i].cakes), args);
                free(args);
            }
        }
    }
    /* Seconds to Units */
    if(begin_exercise(&tester,"seconds_to_units","Sekunden in Stunden und Minuten umrechnen."))
    {
        for (int i = 0; i < TESTS_UNITS; i++)
        {
            if(begin_testcase(&tester))
            {
                int compiled_res = seconds_to_units(exercise_units[i].input_in_seconds);
                int got_seconds = compiled_res & 255;
                int got_minutes = (compiled_res / 256) & 255;
                int got_hours = compiled_res / (256 * 256);
                int compiled_expected = exercise_units[i].expected_seconds + (exercise_units[i].expected_minutes * 256)
                        + (exercise_units[i].expected_hours * 256 * 256);

                char *args = render_exercise_units(exercise_units[i], got_hours, got_minutes, got_seconds);
                assert_int(&tester, compiled_expected, compiled_res, args);
                free(args);
            }
        }
    }
    /* Is Square Root */
    if(begin_exercise(&tester,"is_square_root","Überprüfen ob eine Zahl eine Quadratzahl ist."))
    {
        for (int i = 0; i < TESTS_ROOT; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_root_sum_reverse(exercise_root[i]);
                assert_int(&tester, exercise_root[i].expected_bool, is_square_root(exercise_root[i].n), args);
                free(args);
            }
        }
    }
    /* Digit Sum */
    if(begin_exercise(&tester, "digit_sum", "Die Quersumme einer Zahl ausgeben."))
    {
        for (int i = 0; i < TESTS_SUM; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_root_sum_reverse(exercise_sum[i]);
                    assert_int(&tester, exercise_sum[i].result, digit_sum(exercise_sum[i].n), args);
                    free(args);
                }
            }
        }
    }
    /* Reverse Digits */
    if(begin_exercise(&tester, "reverse_digits", "Die Ziffern-Reihenfolge einer Zahl umkehren."))
    {
        for (int i = 0; i < TESTS_REVERSE; i++)
        {
            if(begin_testcase(&tester))
            {
                if (tester.successful)
                {
                    char *args = render_exercises_root_sum_reverse(exercise_reverse[i]);
                    assert_int(&tester, exercise_reverse[i].result, reverse_digits(exercise_reverse[i].n), args);
                    free(args);
                }
            }
        }
    }

    return wrap_up(&tester);
}