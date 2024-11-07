/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "02ex.c"
#include "testrunner.c"
#include "prng.h"
#include "String.h"

#define TEST_NAME "02ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_1 5
#define TEST_CASES_2 5

typedef struct TestCase_ {
    size_t len;
    uint8_t *arr;
    size_t count;
    char *name;
    char *file_in;
} TestCase;

static TestCase test_cases1[TEST_CASES_1] = {
    {.len = 36, .arr = NULL, .count = 36, .name = "selection_sort1", .file_in = "selection_sort1.png"},
    {.len = 25, .arr = NULL, .count = 25, .name = "selection_sort2", .file_in = "selection_sort2.png"},
    {.len = 9, .arr = NULL, .count = 9, .name = "selection_sort3", .file_in = "selection_sort3.png"},
    {.len = 2, .arr = NULL, .count = 2, .name = "selection_sort4", .file_in = "selection_sort4.png"},
    {.len = 1, .arr = NULL, .count = 1, .name = "selection_sort5", .file_in = "selection_sort5.png"},
};

static TestCase test_cases2[TEST_CASES_2] = {
    {.len = 36, .arr = NULL, .count = 36, .name = "bubble_sort1", .file_in = "bubble_sort1.png"},
    {.len = 25, .arr = NULL, .count = 25, .name = "bubble_sort2", .file_in = "bubble_sort2.png"},
    {.len = 9, .arr = NULL, .count = 9, .name = "bubble_sort3", .file_in = "bubble_sort3.png"},
    {.len = 2, .arr = NULL, .count = 2, .name = "bubble_sort4", .file_in = "bubble_sort4.png"},
    {.len = 1, .arr = NULL, .count = 1, .name = "bubble_sort5", .file_in = "bubble_sort5.png"},
};

char* render_exercise(TestCase testcase)
{
    String s = str_new();
    str_str(&s, "Eingabearray ");
    str_u8s(&s, testcase.arr, testcase.len);
    return s.buf;
}

Canvas canvas_from_file(char *filename)
{
    int path_size = strlen(filename) + strlen(RELATIVE_DIRECTORY_PATH) +1;
    char* path = (char *)malloc(path_size);
    snprintf(path, path_size, "%s%s", RELATIVE_DIRECTORY_PATH, filename);

    Canvas c = canvas_load_image(path);
    free(path);
    return c;
}

int main(int argc, char const *argv[]) {
    test_cases1[0].arr = (uint8_t *) malloc(36);
    for (int i = 0; i < 36; i++) {
        test_cases1[0].arr[i] = randu64() % 256;
    }

    test_cases1[1].arr = (uint8_t *) malloc(25);
    for (int i = 0; i < 25; i++) {
        test_cases1[1].arr[i] = randu64() % 256;
    }

    test_cases1[2].arr = (uint8_t *) malloc(9);
    for (int i = 0; i < 9; i++) {
        test_cases1[2].arr[i] = randu64() % 256;
    }

    test_cases1[3].arr = (uint8_t *) malloc(2);
    for (int i = 0; i < 2; i++) {
        test_cases1[3].arr[i] = randu64() % 256;
    }

    test_cases1[4].arr = (uint8_t *) malloc(1);
    for (int i = 0; i < 1; i++) {
        test_cases1[4].arr[i] = randu64() % 256;
    }



    test_cases2[0].arr = (uint8_t *) malloc(36);
    for (int i = 0; i < 36; i++) {
        test_cases2[0].arr[i] = randu64() % 256;
    }

    test_cases2[1].arr = (uint8_t *) malloc(25);
    for (int i = 0; i < 25; i++) {
        test_cases2[1].arr[i] = randu64() % 256;
    }

    test_cases2[2].arr = (uint8_t *) malloc(9);
    for (int i = 0; i < 9; i++) {
        test_cases2[2].arr[i] = randu64() % 256;
    }

    test_cases2[3].arr = (uint8_t *) malloc(2);
    for (int i = 0; i < 2; i++) {
        test_cases2[3].arr[i] = randu64() % 256;
    }

    test_cases2[4].arr = (uint8_t *) malloc(1);
    for (int i = 0; i < 1; i++) {
        test_cases2[4].arr[i] = randu64() % 256;
    }


    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    // /* Aufgabe 1*/
    if (begin_exercise(&tester, "selection_sort", "Aufgabe 2: selection_sort."))
    {
        for (size_t i = 0; i < TEST_CASES_2; i++) {
            if(begin_testcase(&tester)) {
                uint8_t *input_arr = copy_u8s(test_cases1[i].arr, test_cases1[i].len);
                
                Visualizer v = new_visualizer(test_cases1[i].len, test_cases1[i].count);
                selection_sort(&v, input_arr, test_cases1[i].len);
                Canvas got_c = visualizer_to_canvas(&v, test_cases1[i].name);
                // canvas_save_debug(got_c);

                Canvas expected = canvas_from_file(test_cases1[i].file_in);

                char *args = render_exercise(test_cases1[i]);
                assert_canvas(&tester, expected, got_c, args);
                free(args);

                free(input_arr);
                canvas_free(got_c);
                canvas_free(expected);
                free_visualizer(v);
            }

            free(test_cases1[i].arr);
        }
    }

    // /* Aufgabe 2*/
    if (begin_exercise(&tester, "bubble_sort", "Aufgabe 2: bubble_sort."))
    {
        for (size_t i = 0; i < TEST_CASES_2; i++) {
            if(begin_testcase(&tester)) {
                uint8_t *input_arr = copy_u8s(test_cases2[i].arr, test_cases2[i].len);
                
                Visualizer v = new_visualizer(test_cases2[i].len, test_cases2[i].count);
                bubble_sort(&v, input_arr, test_cases2[i].len);
                Canvas got_c = visualizer_to_canvas(&v, test_cases2[i].name);
                // canvas_save_debug(got_c);

                Canvas expected = canvas_from_file(test_cases2[i].file_in);

                char *args = render_exercise(test_cases2[i]);
                assert_canvas(&tester, expected, got_c, args);
                free(args);

                free(input_arr);
                canvas_free(got_c);
                canvas_free(expected);
                free_visualizer(v);
            }

            free(test_cases2[i].arr);
        }
    }

    return wrap_up(&tester);
}
