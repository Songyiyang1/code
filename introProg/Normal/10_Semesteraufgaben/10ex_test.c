/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "10ex.c"
#include "testrunner.c"
#include "prng.h"
#include "String.h"

#define TEST_NAME "10ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES_1 6
#define TEST_CASES_2 4

typedef struct TestCase_ {
    size_t len;
    uint8_t *arr;
    size_t count;
    char *name;
    char *file_in;
} TestCase;


static TestCase test_cases1[TEST_CASES_1] = {
    {.len = 5, .arr = (uint8_t[5]){128, 196, 0, 255, 64}, .count = 3, .name = "partition1", .file_in = "partition1.png"},
    {.len = 5, .arr = (uint8_t[5]){128, 64, 0, 255, 196}, .count = 3, .name = "partition2", .file_in = "partition2.png"},
    {.len = 9, .arr = (uint8_t[9]){64, 192, 224, 128, 32, 0, 255, 128, 96}, .count = 3, .name = "partition3", .file_in = "partition3.png"},
    {.len = 5, .arr = (uint8_t[5]){0, 64, 128, 196, 255}, .count = 1, .name = "partition4", .file_in = "partition4.png"},
    {.len = 5, .arr = (uint8_t[5]){255, 196, 128, 64, 0}, .count = 5, .name = "partition5", .file_in = "partition5.png"},
    {.len = 5, .arr = (uint8_t[5]){128, 128, 128, 128, 128}, .count = 1, .name = "partition6", .file_in = "partition6.png"},
};

static TestCase test_cases2[TEST_CASES_2] = {
    {.len = 9, .arr = (uint8_t[9]){0, 32, 64, 96, 128, 160, 192, 224, 255}, .count = 7, .name = "sort1", .file_in = "sort1.png"},
    {.len = 9, .arr = (uint8_t[9]){0, 32, 64, 96, 128, 160, 192, 224, 255}, .count = 7, .name = "sort2", .file_in = "sort2.png"},
    {.len = 9, .arr = (uint8_t[9]){0, 32, 64, 96, 128, 160, 192, 224, 255}, .count = 6, .name = "sort3", .file_in = "sort3.png"},
    {.len = 127, .arr = (uint8_t[128]){0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54,56, 58, 60, 62, 64, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 255}, .count = 88, .name = "sort4", .file_in = "sort4.png"},
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

    for (size_t i = 0; i < TEST_CASES_2; i ++) {
        randomly_permute_u8s(test_cases2[i].arr, test_cases2[i].len);
    }


    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");
    


    /* Aufgabe 1*/
    if (begin_exercise(&tester, "visualize_partition", "Aufgabe 1: Partition Algorithmus visualisieren."))
    {
        for (size_t i = 0; i < TEST_CASES_1; i++) {
            if(begin_testcase(&tester)) {
                uint8_t *input_arr = copy_u8s(test_cases1[i].arr, test_cases1[i].len);
                
                Visualizer v = new_visualizer(test_cases1[i].len, test_cases1[i].count);
                // v.colors = Inferno;
                visualize_partition(&v, input_arr, test_cases1[i].len);
                Canvas got_c = visualizer_to_canvas(&v, test_cases1[i].name);
                canvas_save_debug(got_c);

                Canvas expected = canvas_from_file(test_cases1[i].file_in);

                char *args = render_exercise(test_cases1[i]);
                assert_canvas(&tester, expected, got_c, args);
                free(args);

                free(input_arr);
                canvas_free(got_c);
                canvas_free(expected);
                free_visualizer(v);
            }
        }
    }

    /* Aufgabe 2*/
    if (begin_exercise(&tester, "sort_quickly", "Aufgabe 2: Quicksort implementieren."))
    {
        for (size_t i = 0; i < TEST_CASES_2; i++) {
            if(begin_testcase(&tester)) {
                uint8_t *input_arr = copy_u8s(test_cases2[i].arr, test_cases2[i].len);
                
                Visualizer v = new_visualizer(test_cases2[i].len, test_cases2[i].count);
                // v.colors = Inferno;
                sort_quickly(&v, input_arr, test_cases2[i].len);
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
        }
    }

    return wrap_up(&tester);
}
