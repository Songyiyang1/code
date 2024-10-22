/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "08practice.c"
#include "testrunner.c"

#define TEST_NAME "08practice_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_MINIMUM 6
#define TESTS_SEVEN 7
#define TESTS_COUNTDOWN 4
#define TESTS_VALUE 4
#define TESTS_LATIN 12
#define TESTS_MAGIC 6


typedef struct TestMinimum
{
    uint16_t* input_array;
    size_t array_length;
    uint16_t expected;
} exercise_minimum_data;

typedef struct TestSeven
{
    uint16_t* input_array;
    size_t array_length;
    uint16_t* expected;
} exercise_seven_data;

typedef struct TestCountdown
{
    uint16_t* input_array;
    size_t array_length;
    uint16_t* expected_array;
} exercise_countdown_data;

typedef struct TestValue
{
    uint16_t* input_array;
    size_t width;
    size_t height;
    size_t x_coordinate;
    size_t y_coordinate;
    uint16_t expected;
} exercise_value_data;

typedef struct TestsSquare
{
    uint16_t* input_array;
    size_t array_length;
    bool expected;
} exercises_latin_magic_data;

static uint16_t minimum_array1[1] = {1};
static uint16_t minimum_array2[8] = {7,6,5,4,3,2,1,0};
static uint16_t minimum_array3[5] = {100,200,50,40,99};
static uint16_t minimum_array4[6] = {42,123,256,999,2023,10000};
static uint16_t minimum_array5[13] = {64,872,12334,764,153,734,95,2,12,452,63,13,6};
static uint16_t minimum_array6[5] = {2244,4488,8866,6622,2244};

static exercise_minimum_data exercise_minimum [TESTS_MINIMUM] = {
    {.input_array = minimum_array1, .array_length = 1, .expected = 1},
    {.input_array = minimum_array2, .array_length = 8, .expected = 0},
    {.input_array = minimum_array3, .array_length = 5, .expected = 40},
    {.input_array = minimum_array4, .array_length = 6, .expected = 42},
    {.input_array = minimum_array5, .array_length = 13, .expected = 2},
    {.input_array = minimum_array6, .array_length = 5, .expected = 2244},
};

static uint16_t seven_array1[1] = {7};
static uint16_t seven_array2[4] = {5,6,8,9};
static uint16_t seven_array3[7] = {1,2,3,4,5,6,7};
static uint16_t seven_array4[13] = {43,42,41,36,35,34,27,26,25,7,14,13,12};
static uint16_t seven_array5[3] = {7,7,7};
static uint16_t seven_array6[11] = {2,3,5,7,11,13,17,19,23,29,31};
static uint16_t seven_array7[15] = {2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

static exercise_seven_data exercise_seven [TESTS_SEVEN] = {
    {.input_array = seven_array1, .array_length = 1, .expected = seven_array1},
    {.input_array = seven_array2, .array_length = 4, .expected = NULL},
    {.input_array = seven_array3, .array_length = 7, .expected = (seven_array3+6)},
    {.input_array = seven_array4, .array_length = 13, .expected = (seven_array4+9)},
    {.input_array = seven_array5, .array_length = 3, .expected = seven_array5},
    {.input_array = seven_array6, .array_length = 11, .expected = (seven_array6+3)},
    {.input_array = seven_array7, .array_length = 16, .expected = NULL},
};

static uint16_t countdown_input_array1[1] = {0};
static uint16_t countdown_output_array1[1] = {0};
static uint16_t countdown_input_array2[3] = {0,0,0};
static uint16_t countdown_output_array2[3] = {2,1,0};
static uint16_t countdown_input_array3[8] = {0,0,0,0,0,0,0,0};
static uint16_t countdown_output_array3[8] = {7,6,5,4,3,2,1,0};
static uint16_t countdown_input_array4[42] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                              0,0,0,0,0};
static uint16_t countdown_output_array4[42] = {41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,
                                               18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};


static exercise_countdown_data exercise_countdown [TESTS_COUNTDOWN] = {
    {.input_array = countdown_input_array1, .array_length = 1, .expected_array = countdown_output_array1},
    {.input_array = countdown_input_array2, .array_length = 3, .expected_array = countdown_output_array2},
    {.input_array = countdown_input_array3, .array_length = 8, .expected_array = countdown_output_array3},
    {.input_array = countdown_input_array4, .array_length = 42, .expected_array = countdown_output_array4},
};

static uint16_t value_array1[6] = {0,1,2,3,4,5};
static uint16_t value_array2[9] = {0,1,2,3,4,5,6,7,8};
static uint16_t value_array3[10] = {10,100,1,1000,10000,100,10,1,1000,10000};
static uint16_t value_array4[25] = {1,2,3,4,5,2,4,6,8,10,3,6,9,12,15,4,8,12,16,20,5,10,15,20,25};

static exercise_value_data exercise_value [TESTS_VALUE] = {
    {.input_array = value_array1, .width = 3, .height = 2, .x_coordinate = 1, .y_coordinate = 0, .expected = 1},
    {.input_array = value_array2, .width = 3, .height = 3, .x_coordinate = 1, .y_coordinate = 1, .expected = 4},
    {.input_array = value_array3, .width = 10, .height = 1, .x_coordinate = 5, .y_coordinate = 0, .expected = 100},
    {.input_array = value_array4, .width = 5, .height = 5, .x_coordinate = 4, .y_coordinate = 4, .expected = 25},
};

static uint16_t latin_array1a[1] = {42};
static uint16_t latin_array2a[4] = {1,2,3,4};
static uint16_t latin_array2b[4] = {1,2,1,2};
static uint16_t latin_array2c[4] = {1,2,2,1};
static uint16_t latin_array3a[9] = {1,2,3,4,5,6,7,8,9};
static uint16_t latin_array3b[9] = {1,2,3,2,3,1,3,1,2};
static uint16_t latin_array3c[9] = {13,17,11,17,11,13,17,13,11};
static uint16_t latin_array4a[16] = {2,4,8,16,16,8,4,2,4,8,16,16,8,4,2};
static uint16_t latin_array4b[16] = {2,4,8,16,32,64,128,256,256,128,64,32,16,8,4,2};
static uint16_t latin_array5a[25] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5,5,4,3,2,1,5,5,5,5,5};
static uint16_t latin_array5b[25] = {1,2,3,4,5,2,3,4,5,1,3,4,5,1,2,4,5,1,2,3,5,1,2,3,4};
static uint16_t latin_array6a[36] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

static exercises_latin_magic_data exercise_latin [TESTS_LATIN] = {
    {.input_array = latin_array1a, .array_length = 1, .expected = true},
    {.input_array = latin_array2a, .array_length = 2, .expected = true},
    {.input_array = latin_array2b, .array_length = 2, .expected = false},
    {.input_array = latin_array2c, .array_length = 2, .expected = true},
    {.input_array = latin_array3a, .array_length = 3, .expected = true},
    {.input_array = latin_array3b, .array_length = 3, .expected = true},
    {.input_array = latin_array3c, .array_length = 3, .expected = false},
    {.input_array = latin_array4a, .array_length = 4, .expected = false},
    {.input_array = latin_array4b, .array_length = 4, .expected = true},
    {.input_array = latin_array5a, .array_length = 5, .expected = false},
    {.input_array = latin_array5b, .array_length = 5, .expected = true},
    {.input_array = latin_array6a, .array_length = 6, .expected = false},
};

static uint16_t magic_array1[1] = {42};
static uint16_t magic_array2[4] = {1,2,2,1};
static uint16_t magic_array3[9] = {1,2,3,3,1,2,2,3,1};
static uint16_t magic_array4[16] = {4,3,2,1,3,4,1,2,2,1,4,3,1,2,3,4};
static uint16_t magic_array5[25] = {16,2,2,2,2,2,2,2,16,2,2,16,2,2,2,2,2,2,2,16,2,2,16,2,2};
static uint16_t magic_array6[36] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

static exercises_latin_magic_data exercise_magic [TESTS_MAGIC] = {
    {.input_array = magic_array1, .array_length = 1, .expected = true},
    {.input_array = magic_array2, .array_length = 2, .expected = false},
    {.input_array = magic_array3, .array_length = 3, .expected = false},
    {.input_array = magic_array4, .array_length = 4, .expected = false},
    {.input_array = magic_array5, .array_length = 5, .expected = true},
    {.input_array = magic_array6, .array_length = 6, .expected = true},
};

char* render_exercises_minimum_seven_squares( uint16_t arr[], size_t arr_len)
{
    const char *length = format_uint(arr_len);
    const char* array_string = format_uint16_array(arr, arr_len);

    int len = strlen("Wir testen auf dem folgenden Array der Länge ") + strlen(length) + strlen(":\n" TESTRUNNER_LABEL "\t")
              + strlen(array_string) + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf dem folgenden Array der Länge %s:\n" TESTRUNNER_LABEL "\t%s",length, array_string);

    free((char*) length);
    free((char*) array_string);
    return str;
}
char* render_exercise_countdown( size_t arr_len)
{
    const char *length = format_uint(arr_len);

    int len = strlen("Wir testen mit einem Array der Länge ") + strlen(length) + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen mit einem Array der Länge %s",length);

    free((char*) length);
    return str;
}

char* render_exercise_value( exercise_value_data testcase)
{
    const char *width = format_uint(testcase.width);
    const char *height = format_uint(testcase.height);
    const char *x = format_uint(testcase.x_coordinate);
    const char *y = format_uint(testcase.y_coordinate);
    const char* array_string = format_uint16_array(testcase.input_array, testcase.width*testcase.height);

    int len = strlen("Wir testen auf dem folgenden Array mit der Breite ") + strlen(width) + strlen("und der Höhe ")
            + strlen(height) + strlen(":\n" TESTRUNNER_LABEL "\t") + strlen(array_string) + strlen("\n" TESTRUNNER_LABEL)
            + strlen("an der Koordinate (,)") + strlen(x) + strlen(y) + 1;

    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf dem folgenden Array der Breite %s und Höhe %s:"
                       "\n" TESTRUNNER_LABEL "\t%s\n" TESTRUNNER_LABEL "an der Koordinate (%s,%s)",
                       width, height, array_string, x, y);

    free((char*) width);
    free((char*) height);
    free((char*) x);
    free((char*) y);
    free((char*) array_string);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Get Minimum */
    if(begin_exercise(&tester,"get_minimum","Das Minimum des Arrays zurückgeben."))
    {
        for (int i = 0; i < TESTS_MINIMUM; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_minimum_seven_squares(exercise_minimum[i].input_array,
                                                                    exercise_minimum[i].array_length);
                assert_uint(&tester, exercise_minimum[i].expected, get_minimum(exercise_minimum[i].input_array,
                                                                               exercise_minimum[i].array_length), args);
                free(args);
            }
        }
    }
    /* Find Seven */
    if(begin_exercise(&tester,"find_seven","Die erste 7 im Array finden."))
    {
        for (int i = 0; i < TESTS_SEVEN; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_minimum_seven_squares(exercise_seven[i].input_array,
                                                                    exercise_seven[i].array_length);
                assert_pointer(&tester, exercise_seven[i].expected, find_seven(exercise_seven[i].input_array,
                                                                               exercise_seven[i].array_length), args);
                free(args);
            }
        }
    }
    /* Countdown */
    if(begin_exercise(&tester,"countdown","Das Array abwärtszählend füllen."))
    {
        for (int i = 0; i < TESTS_COUNTDOWN; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_countdown(exercise_countdown[i].array_length);
                countdown(exercise_countdown[i].input_array, exercise_countdown[i].array_length);
                assert_uint16_array(&tester, exercise_countdown[i].expected_array, exercise_countdown[i].input_array,
                                    exercise_countdown[i].array_length, args);
                free(args);
            }
        }
    }
    /* Get Value */
    if(begin_exercise(&tester,"get_value","Den Wert bei (x,y) zurückgeben."))
    {
        for (int i = 0; i < TESTS_VALUE; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_value(exercise_value[i]);
                uint16_t got = get_value(exercise_value[i].input_array, exercise_value[i].width, exercise_value[i].height,
                          exercise_value[i].x_coordinate, exercise_value[i].y_coordinate);
                assert_uint(&tester, exercise_value[i].expected, got, args);
                free(args);
            }
        }
    }
    /* Is Latin Square */
    if(begin_exercise(&tester,"is_latin_square","Überprüfen ob das Array ein lateinisches Quadrat ist."))
    {
        for (int i = 0; i < TESTS_LATIN; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_minimum_seven_squares(exercise_latin[i].input_array,
                                                                    exercise_latin[i].array_length * exercise_latin[i].array_length);
                assert_bool(&tester, exercise_latin[i].expected,
                            is_latin_square(exercise_latin[i].input_array, exercise_latin[i].array_length),args);
                free(args);
            }
        }
    }
    /* Is Magic Square */
    if(begin_exercise(&tester,"is_magic_square","Überprüfen ob das Array ein magisches Quadrat ist."))
    {
        for (int i = 0; i < TESTS_MAGIC; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_minimum_seven_squares(exercise_magic[i].input_array,
                                                                    exercise_magic[i].array_length * exercise_magic[i].array_length);
                assert_bool(&tester, exercise_magic[i].expected,
                            is_magic_square(exercise_magic[i].input_array, exercise_magic[i].array_length),args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}
