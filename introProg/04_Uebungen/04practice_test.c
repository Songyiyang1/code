/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "04practice.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "04practice_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_KAPREKAR 15
#define TESTS_PLOT 1

typedef struct TestsKaprekar
{
    int x;
    int expected;
} exercise_kaprekar_data;

typedef struct TestsPlot
{
    char* filename;
} exercise_plot_data;

static exercise_kaprekar_data exercise_kaprekar [TESTS_KAPREKAR] = {
        {.x = 1, .expected = 6},
        {.x = 297, .expected = 3},
        {.x = 111, .expected = 1},
        {.x = 223, .expected = 6},
        {.x = 567, .expected = 5},
        {.x = 42, .expected = 3},
        {.x = 10, .expected = 6},
        {.x = 495, .expected = 0},
        {.x = 77, .expected = 3},
        {.x = 123, .expected = 5},
        {.x = 444, .expected = 1},
        {.x = 91, .expected = 5},
        {.x = 842, .expected = 2},
        {.x = 998, .expected = 6},
        {.x = 999, .expected = 1},
};

static exercise_plot_data exercise_plot [TESTS_PLOT] = {
        {.filename = "plot_kaprekar_expected.png"},
};

Canvas canvas_from_file(char *filename)
{
    int path_size = strlen(filename) + strlen(RELATIVE_DIRECTORY_PATH) +1;
    char* path = (char *)malloc(path_size);
    snprintf(path, path_size, "%s%s", RELATIVE_DIRECTORY_PATH, filename);

    Canvas c = canvas_load_image(path);
    free(path);
    return c;
}

char* render_exercise_kaprekar(exercise_kaprekar_data testcase)
{
    const char *x = format_int(testcase.x);
    int len = strlen("x = ") + strlen(x) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "x = %s", x);
    free((char*) x);
    return str;
}
char* render_exercise_plot(Canvas testcase)
{
    const char *width = format_int(testcase->width);
    const char *height = format_int(testcase->height);
    int len = strlen("Wir testen auf einem ") + strlen(width) +
              strlen("x") + strlen(height) + strlen(" Pixel Canvas.") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas.", width, height);
    free((char*) width);
    free((char*) height);
    return str;
}


int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Kaprekar Count Steps */
    if(begin_exercise(&tester,"kaprekar_count_steps","Die Schritte berechnen, bis eine Kaprekar-Konstante gefunden ist."))
    {
        for (int i = 0; i < TESTS_KAPREKAR; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_kaprekar(exercise_kaprekar[i]);
                assert_int(&tester, exercise_kaprekar[i].expected, kaprekar_count_steps(exercise_kaprekar[i].x), args);
                free(args);
            }
        }
    }
    /* Plot Kaprekar */
    if(begin_exercise(&tester,"plot_kaprekar","Die Pixel schwarz färben, bei denen die x-Koordinate nach einem "
                                              "Sortieren-und-Subtrahieren-Schritt gleich der y-Koordinate ist."))
    {
        for(int i = 0; i < TESTS_PLOT; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_plot[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "plot_kaprekar");

                char *args = render_exercise_plot(expected);
                assert_canvas(&tester, expected, plot_kaprekar(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }

    return wrap_up(&tester);
}