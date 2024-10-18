#include "05practice.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "05practice_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#define TESTS_LINE 4
#define TESTS_DIGITS 12
#define TESTS_PYRAMID 2
#define TESTS_2A 13
#define TESTS_2B 7
#define TESTS_CHESS_RECTANGLE 5
#define TESTS_BINOMIAL 21
#define TESTS_TRICKY 12

typedef struct TestsLine
{
    int x_coordinate;
    int y_coordinate;
    int height;
    char* filename;
} exercise_line_data;

typedef struct TestsDigitsFibonacciTricky
{
    int n;
    int expected;
} exercises_digits_fibonacci_tricky_data;

typedef struct Test2a
{
    int b;
    int exp;
    int expected;
} exercise_2a_data;

typedef struct Test2b
{
    int n;
    int start_coord;
    char *filename;
} exercise_2b_data;

typedef struct TestsPyramid
{
    char* filename;
} exercise_pyramid_data;

typedef struct TestsChessRectangle
{
    int x;
    int y;
    int width;
    int height;
    char* filename;
} exercise_chess_rectangle_data;

typedef struct TestsBinomial
{
    int n;
    int k;
    int expected;
} exercise_binomial_data;

static exercise_line_data exercise_line [TESTS_LINE] = {
        {.x_coordinate = 17, .y_coordinate = 68, .height = 34, .filename = "vertical_line_short_expected.png"},
        {.x_coordinate = 76, .y_coordinate = 19, .height = 152, .filename = "vertical_line_long_expected.png"},
        {.x_coordinate = 125, .y_coordinate = 0, .height = 250, .filename = "vertical_line_full_expected.png"},
        {.x_coordinate = 100, .y_coordinate = 200, .height = 400, .filename = "vertical_line_partial_expected.png"},
};

static exercises_digits_fibonacci_tricky_data exercise_digits [TESTS_DIGITS] = {
        {.n = 1, .expected = 1},
        {.n = 10, .expected = 2},
        {.n = 100, .expected = 3},
        {.n = 0, .expected = 1},
        {.n = 15, .expected = 2},
        {.n = 42, .expected = 2},
        {.n = 55, .expected = 2},
        {.n = 845, .expected = 3},
        {.n = 2023, .expected = 4},
        {.n = 365, .expected = 3},
        {.n = 40000, .expected = 5},
        {.n = 9001, .expected = 4},
};

static exercise_pyramid_data exercise_pyramid [TESTS_PYRAMID] = {
        {.filename = "pyramid_small_expected.png"},
        {.filename = "pyramid_large_expected.png"},
};

static exercise_2a_data exercise_2a [TESTS_2A] = {
        { .b = 1, .exp = 7, .expected = 1},
        { .b = 3, .exp = 2, .expected = 9},
        { .b = 7, .exp = 1, .expected = 7},
        { .b = 2, .exp = 8, .expected = 256},
        { .b = 5, .exp = 0, .expected = 1},
        { .b = 0, .exp = 5, .expected = 0},
        { .b = 0, .exp = 0, .expected = 1},
        { .b = 10, .exp = 6, .expected = 1000000},
        { .b = 2, .exp = 8, .expected = 256},
        { .b = 12, .exp = 3, .expected = 1728},
        { .b = 3, .exp = 3, .expected = 27},
        { .b = 4, .exp = 4, .expected = 256},
        { .b = 5, .exp = 5, .expected = 3125},
};

static exercise_2b_data exercise_2b [TESTS_2B] = {
        { .n = 0, .start_coord = 0, .filename = "exercise_2b_order_0_expected.png"},
        { .n = 1, .start_coord = 0, .filename = "exercise_2b_order_1_expected.png"},
        { .n = 2, .start_coord = 0, .filename = "exercise_2b_order_2_expected.png"},
        { .n = 3, .start_coord = 0, .filename = "exercise_2b_order_3_expected.png"},
        { .n = 4, .start_coord = 0, .filename = "exercise_2b_order_4_expected.png"},
        { .n = 5, .start_coord = 0, .filename = "exercise_2b_order_5_expected.png"},
        { .n = 6, .start_coord = 0, .filename = "exercise_2b_order_6_expected.png"},
};

static exercise_chess_rectangle_data exercise_chess_rectangle [TESTS_CHESS_RECTANGLE] = {
        {.x = 65, .y = 65, .width = 65, .height = 65, .filename = "chess_rectangle_simple_expected.png"},
        {.x = 97, .y = 24, .width = 1, .height = 156, .filename = "chess_rectangle_line_expected.png"},
        {.x = 77, .y = 13, .width = 1, .height = 1, .filename = "chess_rectangle_dot_expected.png"},
        {.x = 0, .y = 0, .width = 300, .height = 300, .filename = "chess_rectangle_full_expected.png"},
        {.x = 9, .y = 6, .width = 3, .height = 3, .filename = "chess_rectangle_rubics_expected.png"},
};

static exercise_binomial_data exercise_binomial [TESTS_BINOMIAL] = {
        {.n = 0, .k = 0, .expected = 1},
        {.n = 1, .k = 1, .expected = 1},
        {.n = 7, .k = 6, .expected = 7},
        {.n = 13, .k = 7, .expected = 1716},
        {.n = 3, .k = 3, .expected = 1},
        {.n = 8, .k = 6, .expected = 28},
        {.n = 42, .k = 0, .expected = 1},
        {.n = 14, .k = 5, .expected = 2002},
        {.n = 25, .k = 5, .expected = 53130},
        {.n = 5, .k = 0, .expected = 1},
        {.n = 25, .k = 1, .expected = 25},
        {.n = 9, .k = 1, .expected = 9},
        {.n = 7, .k = 7, .expected = 1},
        {.n = 13, .k = 2, .expected = 78},
        {.n = 9, .k = 7, .expected = 36},
        {.n = 3, .k = 3, .expected = 1},
        {.n = 13, .k = 0, .expected = 1},
        {.n = 16, .k = 8, .expected = 12870},
        {.n = 8, .k = 4, .expected = 70},
        {.n = 4, .k = 2, .expected = 6},
        {.n = 42, .k = 42, .expected = 1},
};

static exercises_digits_fibonacci_tricky_data exercise_tricky [TESTS_TRICKY] = {
        {.n = 1, .expected = 2},
        {.n = 2, .expected = 3},
        {.n = 3, .expected = 5},
        {.n = 0, .expected = 1},
        {.n = 8, .expected = 55},
        {.n = 4, .expected = 8},
        {.n = 5, .expected = 13},
        {.n = 9, .expected = 89},
        {.n = 10, .expected = 144},
        {.n = 7, .expected = 34},
        {.n = 6, .expected = 21},
        {.n = 20, .expected = 17711},
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

char* render_exercise_line(Canvas t, exercise_line_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);
    const char *line_height = format_int(testcase.height);
    const char *x = format_int(testcase.x_coordinate);
    const char *y = format_int(testcase.y_coordinate);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height)
            + strlen(" Pixel Canvas mit einer Linie der Länge") + strlen(line_height)
            + strlen(" startend bei (") + strlen(x) + strlen(",") + strlen(y) + strlen(").") + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit einer Linie der Länge %s startend "
                       "bei (%s,%s).", width, height, line_height, x, y);
    free((char*) width);
    free((char*) height);
    free((char*) line_height);
    free((char*) x);
    free((char*) y);
    return str;
}

char* render_exercises_digits_fibonacci_tricky(exercises_digits_fibonacci_tricky_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

char* render_exercise_2a(exercise_2a_data testcase)
{
    const char *b = format_int(testcase.b);
    const char *exp = format_int(testcase.exp);
    int len = strlen("b = ") + strlen(b) + strlen(" und exp = ") + strlen(exp) + 1;
    char *str = malloc(len);
    snprintf(str, len, "b = %s und exp = %s", b, exp);
    free((char*) b);
    free((char*) exp);
    return str;
}
char* render_exercise_2b(exercise_2b_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = malloc(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}

char* render_exercise_pyramid(Canvas testcase)
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
char* render_exercise_chess_rectangle(Canvas t, exercise_chess_rectangle_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    char* full_input_string = calloc(60, sizeof(char));
    snprintf(full_input_string,100, TESTRUNNER_LABEL "\tStart bei (%d,%d) mit den Maßen %dx%d\n",
             testcase.x, testcase.y, testcase.width, testcase.height );

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height) +
              strlen(" Pixel Canvas mit folgendem Rechteck:\n") + strlen(full_input_string) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgendem Rechteck:\n%s",
             width, height, full_input_string);
    free((char*) width);
    free((char*) height);
    free(full_input_string);
    return str;
}
char* render_exercise_binomial(exercise_binomial_data testcase)
{
    const char *n = format_int(testcase.n);
    const char *k = format_int(testcase.k);
    int len = strlen("n = ") + strlen(n) + strlen(" und k = ") + strlen(k) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s und k = %s", n, k);
    free((char*) n);
    free((char*) k);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Horizontal Line */
    if(begin_exercise(&tester,"vertical_line","Eine vertikale Linie zeichnen."))
    {
        for(int i = 0; i < TESTS_LINE; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_line[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "vertical_line");

                char *args = render_exercise_line(expected, exercise_line[i]);
                assert_canvas(&tester, expected, vertical_line(got, exercise_line[i].x_coordinate,
                                                                 exercise_line[i].y_coordinate,
                                                                 exercise_line[i].height), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Count Digits */
    if(begin_exercise(&tester,"count_digits","Die Anzahl Stellen von n berechnen."))
    {
        for (int i = 0; i < TESTS_DIGITS; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_digits_fibonacci_tricky(exercise_digits[i]);
                assert_int(&tester, exercise_digits[i].expected, count_digits(exercise_digits[i].n), args);
                free(args);
            }
        }
    }
    /* Pyramid */
    if(begin_exercise(&tester,"pyramid","Eine Pyramide rekursiv auf die Canvas zeichnen."))
    {
        for(int i = 0; i < TESTS_PYRAMID; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_pyramid[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "pyramid");

                char *args = render_exercise_pyramid(expected);
                assert_canvas(&tester, expected, pyramid(got), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    
    /* Chessboard Rectangle */
    if(begin_exercise(&tester,"chessboard_rectangle","Ein rechteckiges Schachbrettmuster auf die Canvas zeichnen."))
    {
        for(int i = 0; i < TESTS_CHESS_RECTANGLE; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_chess_rectangle[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "chessboard_rectangle");

                char *args = render_exercise_chess_rectangle(expected, exercise_chess_rectangle[i]);
                assert_canvas(&tester, expected, chessboard_rectangle(got, exercise_chess_rectangle[i].x,
                                                                      exercise_chess_rectangle[i].y,
                                                                      exercise_chess_rectangle[i].width,
                                                                      exercise_chess_rectangle[i].height), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Binomial Coefficient */
    if(begin_exercise(&tester,"binomial_coefficient","Den Binomial-Koeffizienten von n und k berechnen."))
    {
        for (int i = 0; i < TESTS_BINOMIAL; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_binomial(exercise_binomial[i]);
                assert_int(&tester, exercise_binomial[i].expected, binomial_coefficient(exercise_binomial[i].n,
                                                                                        exercise_binomial[i].k), args);
                free(args);
            }
        }
    }

    /* Aufgabe 2a*/
    if(begin_exercise(&tester, "power", "Aufgabe 2a: Berechnung von ganzzahligen Potenzen."))
    {
        for (int i = 0; i < TESTS_2A; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2a(exercise_2a[i]);
                assert_int(&tester, exercise_2a[i].expected, power(exercise_2a[i].b, exercise_2a[i].exp), args);
                free(args);
            }
        }
    }
    /* Aufgabe 2b*/
    if(begin_exercise(&tester,"sierpinski_carpet","Aufgabe 2b: Den Sierpinski-Carpet implementieren."))
    {
        for(int i = 0; i < TESTS_2B; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_2b[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "sierpinski_carpet");

                char *args = render_exercise_2b(exercise_2b[i]);
                int start = exercise_2b[i].start_coord;
                assert_canvas(&tester, expected, sierpinski_carpet(got, exercise_2b[i].n, start, start), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }

    /* Tricky Numbers */
    if(begin_exercise(&tester,"tricky_numbers","Die Anzahl kniffliger Zahlen mit n Stellen zählen."))
    {
        for (int i = 0; i < TESTS_TRICKY; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercises_digits_fibonacci_tricky(exercise_tricky[i]);
                assert_int(&tester, exercise_tricky[i].expected, tricky_numbers(exercise_tricky[i].n), args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}