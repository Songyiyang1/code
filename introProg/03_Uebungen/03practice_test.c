/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "03practice.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "03practice_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_EVEN 12
#define TESTS_ODD 11
#define TESTS_CHESS 3
#define TESTS_STAIRS 6

typedef struct TestsEvenOdd
{
    int x;
    int expected;
} exercises_even_odd_data;

typedef struct TestsCanvas
{
    char* filename;
} exercise_chess_data;

typedef struct pair_
{
    int x;
    int y;
} pair;

typedef struct TestStairs
{
    char *filename;
    size_t number_of_pairs;
    pair *pair_array;
} exercise_stairs_data;

static exercises_even_odd_data exercise_even [TESTS_EVEN] = {
        {.x = 1, .expected = 0},
        {.x = 0, .expected = 1},
        {.x = 10, .expected = 1},
        {.x = 5, .expected = 0},
        {.x = 25, .expected = 0},
        {.x = 26, .expected = 1},
        {.x = 42, .expected = 1},
        {.x = 2023, .expected = 0},
        {.x = 1000, .expected = 1},
        {.x = 512, .expected = 1},
        {.x = 7, .expected = 0},
        {.x = 144, .expected = 1},
};

static exercises_even_odd_data exercise_odd [TESTS_ODD] = {
        {.x = 1, .expected = 1},
        {.x = 0, .expected = 0},
        {.x = 9, .expected = 1},
        {.x = 4, .expected = 0},
        {.x = 37, .expected = 1},
        {.x = 38, .expected = 0},
        {.x = 42, .expected = 0},
        {.x = 2023, .expected = 1},
        {.x = 5555, .expected = 1},
        {.x = 256, .expected = 0},
        {.x = 3, .expected = 1},
};

static pair exercise_stairs_arguments[] = {
        { .x = 25, .y = 25 },
        { .x = 1, .y = 1 },
        { .x = 4, .y = 3 },
        { .x = 9, .y = 16 },
        { .x = 260, .y = 7 },
        { .x = 7, .y = 260 },
};
static exercise_stairs_data exercise_stairs [TESTS_STAIRS] = {
        { .filename = "exercise_ityas_introduction_expected.png",},
        { .filename = "exercise_ityas_baby_steps_expected.png",},
        { .filename = "exercise_ityas_rectangles_one_expected.png",},
        { .filename = "exercise_ityas_rectangles_two_expected.png",},
        { .filename = "exercise_ityas_dwarfed_one_expected.png",},
        { .filename = "exercise_ityas_dwarfed_two_expected.png",},
};

static exercise_chess_data exercise_chess [TESTS_CHESS] = {
        {.filename = "draw_chessboard_original_expected.png"},
        {.filename = "draw_chessboard_bigger_expected.png"},
        {.filename = "draw_chessboard_rectangle_expected.png"},
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
char* render_exercises_even_odd(exercises_even_odd_data testcase)
{
    const char *x = format_int(testcase.x);
    int len = strlen("x = ") + strlen(x) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "x = %s", x);
    free((char*) x);
    return str;
}
char* render_exercises_canvas(Canvas testcase)
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
char* render_exercise_stairs(Canvas testcase,int step_w , int step_h)
{
    const char *width = format_int(testcase->width);
    const char *height = format_int(testcase->height);
    const char *step_width = format_int(step_w);
    const char *step_height = format_int(step_h);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit der Schrittbreite ") + strlen(step_width) + strlen(" und der Schritthöhe ") +
              strlen(step_height) + strlen(".")+ 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit der Schrittbreite %s und der Schritthöhe %s.",
             width, height, step_width, step_height);
    free((char*) width);
    free((char*) height);
    free((char*) step_width);
    free((char*) step_height);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Is Even */
    if(begin_exercise(&tester,"is_even","Überprüfen ob eine Zahl gerade ist."))
    {
        for (int i = 0; i < TESTS_EVEN; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_even_odd(exercise_even[i]);
                assert_int(&tester, exercise_even[i].expected, is_even(exercise_even[i].x), args);
                free(args);
            }
        }
    }
    /* Is Odd */
    if(begin_exercise(&tester,"is_odd","Überprüfen ob eine Zahl ungerade ist."))
    {
        for (int i = 0; i < TESTS_ODD; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_even_odd(exercise_odd[i]);
                assert_int(&tester, exercise_odd[i].expected, is_odd(exercise_odd[i].x), args);
                free(args);
            }
        }
    }
    /* Draw Smiley */
    if(begin_exercise(&tester,"draw_smiley","Einen Smiley auf die Canvas zeichnen."))
    {
        if(begin_testcase(&tester))
        {
            Canvas expected = canvas_from_file("draw_smiley_expected.png");
            Canvas got = canvas_new(expected->width, expected->height, "draw_smiley");

            char *args = render_exercises_canvas(expected);
            assert_canvas(&tester, expected, draw_smiley(got), args);
            free(args);

            canvas_free(got);
            canvas_free(expected);
        }
    }
    /* Draw Chessboard */
    if(begin_exercise(&tester,"draw_chessboard","Die Canvas mit einem Schachbrettmuster einfärben."))
    {
        for(int i = 0; i < TESTS_CHESS; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_chess[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "draw_chessboard");

                char *args = render_exercises_canvas(expected);
                assert_canvas(&tester, expected, draw_chessboard(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* I Told You About Stairs*/
    if(begin_exercise(&tester,"i_told_you_about_stairs","Die Fläche unter Stufen mit variabler Breite "
                                                         "und Höhe einfärben."))
    {
        for(int i = 0; i < TESTS_STAIRS; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_stairs[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "i_told_you_about_stairs");

                char *args = render_exercise_stairs(expected, exercise_stairs_arguments[i].x, exercise_stairs_arguments[i].y);
                assert_canvas(&tester, expected, i_told_you_about_stairs(got, exercise_stairs_arguments[i].x,
                                                                         exercise_stairs_arguments[i].y), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }

    return wrap_up(&tester);
}