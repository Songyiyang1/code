/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "09ex.c"
#include "testrunner.c"
#include "String.h"

#define TEST_NAME "09ex_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_1AB 42
#define TESTS_3 4

typedef struct Test1ab
{
    uint32_t input;
    uint32_t expected;
} exercises_1ab_data;

typedef struct Test2ac
{
    Layer* pancake_creation_array;
    size_t array_length;
} exercises_2ac_data;

typedef struct Test3
{
    uint16_t* expected_array;
    size_t array_length;
} exercise_3_data;


static exercises_1ab_data exercises_1ab [TESTS_1AB] = {
        {.input = 10, .expected = 10}, {.input = 1, .expected = 1}, {.input = 0, .expected = 0},
        {.input = 3, .expected = 3}, {.input = 6, .expected = 6}, {.input = 9, .expected = 9},
        {.input = 25, .expected = 25}, {.input = 50, .expected = 50}, {.input = 100, .expected = 100},
        {.input = 11, .expected = 11}, {.input = 17, .expected = 17}, {.input = 23, .expected = 23},
        {.input = 64, .expected = 64}, {.input = 128, .expected = 128}, {.input = 256, .expected = 256},
        {.input = 2222, .expected = 2222}, {.input = 3333, .expected = 3333}, {.input = 7777, .expected = 7777},
        {.input = 2, .expected = 2}, {.input = 5, .expected = 5}, {.input = 7, .expected = 7},
        {.input = 456, .expected = 456}, {.input = 123, .expected = 123}, {.input = 789, .expected = 789},
        {.input = 54, .expected = 54}, {.input = 13, .expected = 13}, {.input = 96, .expected = 96},
        {.input = 131, .expected = 131}, {.input = 545, .expected = 545}, {.input = 969, .expected = 969},
        {.input = 80, .expected = 80}, {.input = 40, .expected = 40}, {.input = 20, .expected = 20},
        {.input = 1010110, .expected = 1010110}, {.input = 10110101, .expected = 10110101}, {.input = 11101, .expected = 11101},
        {.input = 97, .expected = 97}, {.input = 65, .expected = 65}, {.input = 52, .expected = 52},
        {.input = 9001, .expected = 9001}, {.input = 1337, .expected = 1337}, {.input = 42, .expected = 42},
};

static uint16_t exercise3_expected1 [3] = {1,4,9};
static uint16_t exercise3_expected2 [8] = {1,4,9,16,25,36,49,64};
static uint16_t exercise3_expected3 [13] = {1,4,9,16,25,36,49,64,81,100,121,144,169};
static uint16_t exercise3_expected4 [21] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441};

static exercise_3_data exercise_3 [TESTS_3] = {
        {.array_length = 3, .expected_array = exercise3_expected1},
        {.array_length = 8, .expected_array = exercise3_expected2},
        {.array_length = 13, .expected_array = exercise3_expected3},
        {.array_length = 21, .expected_array = exercise3_expected4},
};

void render_pancake_rec(PileOfPancakes *p, String *s) {
    if (p->further_layers != NULL) {
        render_pancake_rec(p->further_layers, s);
    }

    if (p->layer == ActualPancake) {
        str_str(s, "===       === Actual Pancake ===\n");
    } else if (p->layer == Fruit) {
        str_str(s, "===       •¤0     Fruit      0¤•\n");
    } else {
        str_str(s, "===       ~~@     Cream      @~~\n");
    }
}

char *render_pancake(PileOfPancakes *p) {
    String s = str_new();
    str_str(&s, "\n\n");

    if (p == NULL) {
        str_str(&s, "===   got a NULL pointer instead of a pancake :(\n");
    } else {
        render_pancake_rec(p, &s);
        str_str(&s, "===      ¯¯--------------------¯¯\n");
    }
    return s.buf;
}

bool pancake_ptr_eq(PileOfPancakes *p1, PileOfPancakes *p2) {
    if (p1 == NULL && p2 == NULL) {
        return true;
    } else if (p1 == NULL || p2 == NULL) {
        return false;
    } else {
        if (p1->layer != p2->layer) {
            return false;
        }

        return pancake_ptr_eq(p1->further_layers, p2->further_layers);
    }
}

void assert_pancake(Tester *t, PileOfPancakes *expected, PileOfPancakes *got, const char *context){
    if (!pancake_ptr_eq(expected, got)) {
        const char* s_expected = render_pancake(expected);
        const char* s_got = render_pancake(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

void free_pancake(PileOfPancakes *p) {
    if (p != NULL) {
        free_pancake(p->further_layers);
        free(p);
    }
}

char* render_exercises_2(PileOfPancakes *p)
{
    char *rendered_pile = render_pancake(p);

    size_t len = strlen(rendered_pile) + strlen("Erhielt folgenden Pfannkuchenhaufen:\n\n") + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Erhielt folgenden Pfannkuchenhaufen:\n\n%s", rendered_pile);
    free(rendered_pile);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1a */
    if(begin_exercise(&tester,"return_pointer","Aufgabe 1a: Einen Pointer auf den gleichen Wert zurückgeben."))
    {
        for (int i = 0; i < TESTS_1AB; i++)
        {
            if(begin_testcase(&tester))
            {
                uint32_t* output = return_pointer(exercises_1ab[i].input);
                if(output == NULL){
                    assert_bool(&tester, true, false, "Der NULL-Platzhalter muss noch in der Rückgabe ersetzt werden :).");
                } else {
                    assert_uint(&tester, exercises_1ab[i].expected, *(output), "");
                    free(output);
                }
            }
        }
    }
    /* Aufgabe 1b */
    if(begin_exercise(&tester,"free_pointer","Aufgabe 1b: Einen Pointer freigeben und dessen Wert zurückgeben."))
    {
        for (int i = 0; i < TESTS_1AB; i++)
        {
            if(begin_testcase(&tester))
            {
                uint32_t* input = mallocx(sizeof(uint32_t));
                *input = exercises_1ab[i].input;
                assert_uint(&tester, exercises_1ab[i].expected, free_pointer(input), "");
            }
        }
    }
    /* Aufgabe 2a */
    if(begin_exercise(&tester, "pure_fruit", "Aufgabe 2a: Einschichtiger Fruchtpfannkuchen."))
    {

        if (begin_testcase(&tester)) {
            PileOfPancakes got = pure_fruit();
            PileOfPancakes expected = { .layer = Fruit, .further_layers = NULL };
            assert_pancake(&tester, &expected, &got, "Wir hätten gerne einen Pfannkuchen der lediglich aus einer Fruchtschicht besteht.");
        }
    }
    /* Aufgabe 2b */
    if(begin_exercise(&tester, "pure_fruit_ptr", "Aufgabe 2b: Pointer auf einschichtigen Fruchtpfannkuchen."))
    {

        if (begin_testcase(&tester)) {
            PileOfPancakes *got = pure_fruit_ptr();
            PileOfPancakes expected = { .layer = Fruit, .further_layers = NULL };
            assert_pancake(&tester, &expected, got, "Wir hätten gerne einen Pointer auf einen Pfannkuchen der lediglich aus einer Fruchtschicht besteht.");
            free(got);
        }
    }
    /* Aufgabe 2c */
    if(begin_exercise(&tester, "fruit_crepe_ptr", "Aufgabe 2c: Pointer auf Frucht-Auf-Teig-Pfannkuchen."))
    {

        if (begin_testcase(&tester)) {
            PileOfPancakes *got = fruit_crepe_ptr();
            PileOfPancakes expected_fruit = { .layer = Fruit, .further_layers = NULL };
            PileOfPancakes expected = { .layer = ActualPancake, .further_layers = &expected_fruit };
            assert_pancake(&tester, &expected, got, "Einen Pointer auf Frucht-über-Teig Pfannkuchen, bitte.");
            if (got != NULL && got->further_layers != NULL) {
                free(got->further_layers);
            }
            if (got != NULL) {
                free(got);
            }
        }
    }
    /* Aufgabe 2d */
    if(begin_exercise(&tester, "mille_crepes", "Aufgabe 2d: Ganz viele Teigschichten."))
    {
        for (uint32_t i = 1; i < 22; i++) {
            if (begin_testcase(&tester)) {
                PileOfPancakes got = mille_crepes(i);
                PileOfPancakes expected = { .layer = ActualPancake, .further_layers = NULL };
                PileOfPancakes *top_of_pancake = &expected;
                for (uint32_t j = 1; j < i; j++) {
                    top_of_pancake->further_layers = malloc(sizeof(PileOfPancakes));
                    top_of_pancake->further_layers->layer = ActualPancake;
                    top_of_pancake->further_layers->further_layers = NULL;
                    top_of_pancake = top_of_pancake->further_layers;
                }

                String s = str_new();
                if (i == 1) {
                    str_str(&s, "Eine Teigschicht, bitte.");
                } else {
                    str_uint(&s, i);
                    str_str(&s, " viele Teigschichten, bitte.");
                }

                assert_pancake(&tester, &expected, &got, s.buf);

                free_pancake(expected.further_layers);
                free_pancake(got.further_layers);
                str_free(s);
            }
        }
    }
    /* Aufgabe 3 */
    if(begin_exercise(&tester,"create_dynamic_array","Aufgabe 3: Ein dynamisches Array erstellen."))
    {
        for (int i = 0; i < TESTS_3; i++)
        {
            if(begin_testcase(&tester))
            {
                size_t len = exercise_3[i].array_length;
                uint16_t* output = create_dynamic_array(len);
                if(output == NULL){
                    assert_bool(&tester, true, false, "Der NULL-Platzhalter muss noch in der Rückgabe ersetzt werden :).");
                } else {
                    assert_uint16_array(&tester,exercise_3[i].expected_array, output, len, "");
                    free(output);
                }
            }
        }
    }

    return wrap_up(&tester);
}
