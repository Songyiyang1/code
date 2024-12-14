/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "07ex.c"
#include "testrunner.c"
#include "prng.h"
#include "String.h"

#define TEST_NAME "07ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_2 5

typedef struct TestCase_ {
    size_t len;
    uint8_t *arr;
    size_t count;
    char *name;
    char *file_in;
} TestCase;

static TestCase test_cases2[TEST_CASES_2] = {
    {.len = 64, .arr = NULL, .count = 64, .name = "sort_it1", .file_in = "sort_it1.png"},
    {.len = 32, .arr = NULL, .count = 32, .name = "sort_it2", .file_in = "sort_it2.png"},
    {.len = 8, .arr = NULL, .count = 8, .name = "sort_it3", .file_in = "sort_it3.png"},
    {.len = 2, .arr = NULL, .count = 2, .name = "sort_it4", .file_in = "sort_it4.png"},
    {.len = 1, .arr = NULL, .count = 1, .name = "sort_it5", .file_in = "sort_it5.png"},
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
    test_cases2[0].arr = (uint8_t *) malloc(64);
    for (int i = 0; i < 64; i++) {
        test_cases2[0].arr[i] = randu64() % 256;
    }

    test_cases2[1].arr = (uint8_t *) malloc(32);
    for (int i = 0; i < 32; i++) {
        test_cases2[1].arr[i] = randu64() % 256;
    }

    test_cases2[2].arr = (uint8_t *) malloc(8);
    for (int i = 0; i < 8; i++) {
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
    if (begin_exercise(&tester, "sort_it", "Aufgabe 1: Den Sortieralgorithmus rekonstruieren."))
    {
        for (size_t i = 0; i < TEST_CASES_2; i++) {
            if(begin_testcase(&tester)) {
                uint8_t *input_arr = copy_u8s(test_cases2[i].arr, test_cases2[i].len);
                
                Visualizer v = new_visualizer(test_cases2[i].len, test_cases2[i].count);
                sort_it(&v, input_arr, test_cases2[i].len);
                Canvas got_c = visualizer_to_canvas(&v, test_cases2[i].name);
                canvas_save_debug(got_c);

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
