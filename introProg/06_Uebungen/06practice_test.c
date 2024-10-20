/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include "06practice.c"
#include "testrunner.c"
#include "canvas.h"

#define TEST_NAME "06practice_test"
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"

#define TESTS_TRIANGLE 3
#define TESTS_COLORMIX 7
#define TESTS_ANTIALIASED 3
#define TESTS_OVERFLOW 13
#define TESTS_ANGLE 11

typedef struct TestsTriangles
{
    RGB color_one;
    RGB color_two;
    char* filename;
} exercises_triangle_antialiased_data;

typedef struct TestsColormix
{
    RGB color_one;
    RGB color_two;
    RGB expected;
} exercise_colormix_data;

typedef struct TestOverflow
{
    int n;
    int expected;
} exercise_overflow_data;

typedef struct TestAngles
{
    float x;
    float y;
    float angle;
} exercise_angle_data;

static exercises_triangle_antialiased_data exercise_triangle [TESTS_TRIANGLE] = {
        {.color_one = {1,1,1}, .color_two = {0,0,0}, .filename = "right_triangle_smallbw_expected.png"},
        {.color_one = {1.0,0.0,0.4}, .color_two = {0.0,1.0,0.4}, .filename = "right_triangle_smallcolor_expected.png"},
        {.color_one = {1,0,1}, .color_two = {0,1,1}, .filename = "right_triangle_bigcolor_expected.png"},
};

static exercise_colormix_data exercise_colormix [TESTS_COLORMIX] = {
        {.color_one = {1,1,1}, .color_two = {0,0,0}, .expected = {0.5,0.5,0.5}},
        {.color_one = {0.8,0.8,0.8}, .color_two = {0.25,0.25,0.25}, .expected = {0.525,0.525,0.525}},
        {.color_one = {0.749,1.0,0.0}, .color_two = {1.0,0.65,0.0}, .expected = {0.8745,0.825,0.0}},
        {.color_one = {0.44,0.34,0.3}, .color_two = {0.52,0.12,0.9}, .expected = {0.48,0.23,0.6}},
        {.color_one = {0.25,0.34,0.07}, .color_two = {0.89,0.00,0.19}, .expected = {0.57,0.17,0.13}},
        {.color_one = {0.07,0.91,0.06}, .color_two = {0.11,0.37,1.00}, .expected = {0.09,0.64,0.53}},
        {.color_one = {0.92,0.92,0.06}, .color_two = {0.96,0.60,0.06}, .expected = {0.94,0.76,0.06}},
};

static exercises_triangle_antialiased_data exercise_antialiased [TESTS_ANTIALIASED] = {
        {.color_one = {1,1,1}, .color_two = {0,0,0}, .filename = "antialiased_right_triangle_smallbw_expected.png"},
        {.color_one = {0.8,0.8,0.8}, .color_two = {0.25,0.25,0.25}, .filename = "antialiased_right_triangle_smallgrey_expected.png"},
        {.color_one = {0.749,1.0,0.0}, .color_two = {1.0,0.65,0.0}, .filename = "antialiased_right_triangle_color_expected.png"},
};

static exercise_overflow_data exercise_overflow [TESTS_OVERFLOW] = {
        {.n = 1, .expected = 627},
        {.n = -1, .expected = -1},
        {.n = 12, .expected = 7524},
        {.n = 20, .expected = 12540},
        {.n = 33, .expected = 20691},
        {.n = 100, .expected = -1},
        {.n = 4, .expected = 2508},
        {.n = -25, .expected = -1},
        {.n = 0, .expected = 0},
        {.n = 52, .expected = 32604},
        {.n = 53, .expected = -1},
        {.n = 32768, .expected = -1},
        {.n = -32768, .expected = -1},
};

static exercise_angle_data exercise_angle [TESTS_ANGLE] = {
        {.x = 1, .y = 0, .angle = 0.0},
        {.x = 0, .y = 1, .angle = 90.0},
        {.x = 1, .y = 1, .angle = 45.0},
        {.x = 2, .y = 1, .angle = 26.565052},
        {.x = 1, .y = 2, .angle = 63.434948},
        {.x = 1, .y = -1, .angle = -45.0},
        {.x = -1, .y = 3, .angle = 108.434952},
        {.x = 54, .y = 23, .angle = 23.070412},
        {.x = 109, .y = 72, .angle = 33.446774},
        {.x = 11.12, .y = 13.14, .angle = 49.759735},
        {.x = 400, .y = 2023, .angle = 78.815392},
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
int compare_RGB(RGB expected, RGB got){
    int result = 1;
    if((fabsf(expected.r - got.r) >= 0.0001) || (fabsf(expected.g - got.g) >= 0.0001)
       || (fabsf(expected.b - got.b) >= 0.0001) ){
        result = 0;
    }
    return result;
}

char* render_exercises_triangle_antialiased(Canvas t, exercises_triangle_antialiased_data testcase)
{
    const char *width = format_int(t->width);
    const char *height = format_int(t->height);

    int len1 = strlen(TESTRUNNER_LABEL) + strlen("\tColor1: R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + 1;
    char *color1 = mallocx(len1);
    snprintf(color1, len1, TESTRUNNER_LABEL "\tColor1: R = %.4f G = %.4f B = %.4f", testcase.color_one.r,
             testcase.color_one.g, testcase.color_one.b);
    //The + 6 results from each float in the RGB struct, being printed to four decimal points
    int len2 = strlen(TESTRUNNER_LABEL) + strlen("\tColor2: R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + 1;
    char *color2 = mallocx(len2);
    snprintf(color2, len2, TESTRUNNER_LABEL "\tColor2: R = %.4f G = %.4f B = %.4f", testcase.color_two.r,
             testcase.color_two.g, testcase.color_two.b);

    int len = strlen("Wir testen auf einem ") + strlen(width) + strlen("x") + strlen(height)
              + strlen(" Pixel Canvas mit folgenden zwei Farben:\n") + len1 + len2 + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir testen auf einem %sx%s Pixel Canvas mit folgenden zwei Farben:\n%s\n%s\n", width, height,
             color1, color2);

    free((char*) color1);
    free((char*) color2);
    free((char*) width);
    free((char*) height);
    return str;
}
char* render_exercise_colormix(exercise_colormix_data testcase)
{
    int len1 = strlen(TESTRUNNER_LABEL) + strlen("\tColor1: R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + 1;
    char *color1 = mallocx(len1);
    snprintf(color1, len1, TESTRUNNER_LABEL "\tColor1: R = %.4f G = %.4f B = %.4f", testcase.color_one.r,
             testcase.color_one.g, testcase.color_one.b);
    //The + 6 results from each float in the RGB struct, being printed to four decimal points
    int len2 = strlen(TESTRUNNER_LABEL) + strlen("\tColor2: R = ") + 6 + strlen(" G = ") + 6 + strlen(" B = ") + 6 + 1;
    char *color2 = mallocx(len2);
    snprintf(color2, len2, TESTRUNNER_LABEL "\tColor2: R = %.4f G = %.4f B = %.4f", testcase.color_two.r,
             testcase.color_two.g, testcase.color_two.b);

    int len = strlen("Wir mischen die folgenden zwei Farben:\n") + len1 + len2 + 1;
    char *str = mallocx(len);
    snprintf(str, len, "Wir mischen die folgenden zwei Farben:\n%s\n%s\n", color1, color2);

    free((char*) color1);
    free((char*) color2);

    return str;
}

char* render_exercise_overflow(exercise_overflow_data testcase)
{
    const char *n = format_int(testcase.n);
    int len = strlen("n = ") + strlen(n) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "n = %s", n);
    free((char*) n);
    return str;
}
char* render_exercise_angle(exercise_angle_data testcase)
{
    const char *x = format_float(testcase.x);
    const char *y = format_float(testcase.y);
    int len = strlen("x =  und y = ") + strlen(x) + strlen(y) + 1;
    char *str = mallocx(len);
    snprintf(str, len, "x = %s und y = %s", x, y);
    free((char*) x);
    free((char*) y);
    return str;
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Right Triangle */
    if(begin_exercise(&tester,"right_triangle","Die Pixel anders färben, deren X-Koordinate kleiner gleich "
                                               "ihrer Y-Koordinate ist."))
    {
        for(int i = 0; i < TESTS_TRIANGLE; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_triangle[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "right_triangle");

                char *args = render_exercises_triangle_antialiased(expected, exercise_triangle[i]);

                assert_canvas(&tester, expected, right_triangle(got, exercise_triangle[i].color_one,
                                                               exercise_triangle[i].color_two), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Mix Colors */
    if(begin_exercise(&tester,"mix_colors","Zwei Farben mischen."))
    {
        for(int i = 0; i < TESTS_COLORMIX; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_colormix(exercise_colormix[i]);
                RGB got = mix_colors(exercise_colormix[i].color_one, exercise_colormix[i].color_two);
                assert_struct(&tester, compare_RGB(exercise_colormix[i].expected, got), args);
                free(args);
            }
        }
    }
    /* Antialiased Right Triangle */
    if(begin_exercise(&tester,"antialiased_right_triangle","Die Pixel anders färben, deren X-Koordinate kleiner gleich "
                                               "ihrer Y-Koordinate ist und die entstehende Kante in der "
                                               "Mischfarbe färben."))
    {
        for(int i = 0; i < TESTS_ANTIALIASED; i++)
        {
            if(begin_testcase(&tester))
            {
                Canvas expected = canvas_from_file(exercise_antialiased[i].filename);
                Canvas got = canvas_new(expected->width, expected->height, "antialiased_right_triangle");

                char *args = render_exercises_triangle_antialiased(expected, exercise_antialiased[i]);

                assert_canvas(&tester, expected, antialiased_right_triangle(got, exercise_antialiased[i].color_one,
                                                                exercise_antialiased[i].color_two), args);
                free(args);

                canvas_free(got);
                canvas_free(expected);
            }
        }
    }
    /* Times627 */
    if(begin_exercise(&tester,"times627","Sichere Multiplikation mit Integern."))
    {
        for (int i = 0; i < TESTS_OVERFLOW; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_overflow(exercise_overflow[i]);
                assert_int(&tester, exercise_overflow[i].expected, times627(exercise_overflow[i].n), args);
                free(args);
            }
        }
    }
    /* Compute Angle */
    if(begin_exercise(&tester,"compute_angle","Den Winkel zwischen zwei Linien berechnen."))
    {
        for (int i = 0; i < TESTS_ANGLE; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_angle(exercise_angle[i]);
                assert_float(&tester, exercise_angle[i].angle, compute_angle(exercise_angle[i].x, exercise_angle[i].y),
                             args);
                free(args);
            }
        }
    }

    return wrap_up(&tester);
}