/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <math.h>

#include "05ex.c"
#include "testrunner.c"

#define TEST_NAME "05ex_test"
#ifndef RELATIVE_DIRECTORY_PATH
#define RELATIVE_DIRECTORY_PATH "Testdata/" TEST_NAME "data/"
#endif
#define TEST_CASES 18

typedef struct AsciiCanvas_ {
    uint16_t width;
    uint16_t height;
    char *buffer;
} AsciiCanvas;

AsciiCanvas ascii_new(uint16_t width, uint16_t height) {
    size_t len = height * (width + 1);
    char *buffer = malloc(len + 1);
    buffer[len] = 0;

    for (size_t i = 0; i < len; i++) {
        buffer[i] = ' ';
    }

    for (size_t i = 1; i <= height; i++) {
        buffer[i * (width + 1) - 1] = '\n';
    }

    AsciiCanvas ac = {
        .width = width,
        .height = height,
        .buffer = buffer,
    };
    return ac;
}

void ascii_free(AsciiCanvas ac) {
    free(ac.buffer);
}

void ascii_set(AsciiCanvas *ac, char c, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1) || y >= ac->height) {
        printf("invalid AsciiCanvas set at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    ac->buffer[y * (ac->width + 1) + x] = c;
}

char ascii_get(AsciiCanvas *ac, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1) || y >= ac->height) {
        printf("invalid AsciiCanvas get at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    return ac->buffer[y * (ac->width + 1) + x];
}

char *ascii_get_str(AsciiCanvas *ac, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1)|| y >= ac->height) {
        printf("invalid AsciiCanvas get_str at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    return ac->buffer + (y * (ac->width + 1) + x);
}

void search_tree_free(TreeNode *t) {
    if (t != NULL) {
        search_tree_free(t->left);
        search_tree_free(t->right);
        free(t);
    }
}

bool search_tree_eq(TreeNode *t1, TreeNode *t2) {
    if (t1 == NULL) {
        return t2 == NULL;
    } else if (t2 == NULL) {
        return false;
    } else {
        if (t1->item != t2->item) {
            return false;
        } else {
            return search_tree_eq(t1->left, t2->left) && search_tree_eq(t1->right, t2->right);
        }
    }
}

TreeNode *search_tree_clone(TreeNode *t) {
    if (t == NULL) {
        return NULL;
    } else {
        TreeNode *n = malloc(sizeof(TreeNode));
        n->item = t->item;
        n->left = search_tree_clone(t->left);
        n->right = search_tree_clone(t->right);
        return n;
    }
}

size_t tree_height(TreeNode *t) {
    if (t == NULL) {
        return 0;
    } else {
        size_t left_height = tree_height(t->left);
        size_t right_height = tree_height(t->right);

        if (left_height > right_height) {
            return 1 + left_height;
        } else {
            return 1 + right_height;
        }
    }
}

size_t node_width(uint16_t item) {
    /* The +1s counteract the flooring. */
    return 2 /* [] */ + floor(log10(item)) + 1;
}

size_t tree_width(TreeNode *t, size_t padding /* num horizontal spaces between nodes*/) {
    if (t == NULL) {
        return 0;
    } else {
        size_t left_width = tree_width(t->left, padding);
        size_t right_width = tree_width(t->right, padding);

        size_t own_width = node_width(t->item) + padding;

        return left_width + padding + own_width + right_width;
    }
}

typedef struct DrawingInfo_ {
    uint16_t width;
    uint16_t docking_point; /* The midpoint of the root */
} DrawingInfo;

/* Draws the tree, with the top-left corner of its bounding box at (x, y) */
/* Returns the width of the drawing of this tree. */
DrawingInfo tree_ascii_(TreeNode *t, AsciiCanvas *ac, uint16_t x, uint16_t y, uint16_t padding) {
    if (t == NULL) {
        DrawingInfo ret = { .width = 0, .docking_point = 0};
        return ret;
    }

    uint16_t label_width = node_width(t->item);
    DrawingInfo left_info = tree_ascii_(t->left, ac, x, y + 1, padding);
    uint16_t start_right = x + left_info.width + padding + label_width;
    DrawingInfo right_info = tree_ascii_(t->right, ac, start_right, y + 1, padding);
    uint16_t total_width = left_info.width + padding + label_width + padding + right_info.width;
    uint16_t own_docking_point = left_info.width + (2 * padding + label_width) / 2;

    // printf("width %d, height %d, item %d, left_width %d, label_width %d, right_width %d\n", ac->width, ac->height, t->item, left_info.width, label_width, right_info.width);

    /* draw own label */
    char tmp = ascii_get(ac, x + left_info.width + padding + label_width, y);
    snprintf(ascii_get_str(ac, x + left_info.width + padding, y), label_width + 1, "[%d]", t->item);
    ascii_set(ac, tmp, x + left_info.width + padding + label_width, y);

    if (t->left != NULL) {
        ascii_set(ac, '.', x + left_info.docking_point, y);
        for (uint16_t xi = left_info.docking_point + 1; xi < left_info.width + padding; xi++) {
            ascii_set(ac, '-', x + xi, y);
        }
    }

    if (t->right != NULL) {
        ascii_set(ac, '.', start_right +  right_info.docking_point, y);
        for (uint16_t xi = start_right; xi < start_right + right_info.docking_point; xi++) {
            ascii_set(ac, '-', xi, y);
        }
    }

    DrawingInfo ret = { .width = total_width, .docking_point = own_docking_point};
    return ret;
}

char *tree_ascii(TreeNode *t) {
    size_t padding = 1;
    
    size_t height = tree_height(t);
    size_t width = tree_width(t, padding) + 1;
    size_t len = height * (width + 1);

    if (height == 0) {
        char *empty = "\n(empty tree)\n";
        size_t len = strlen(empty);
        char *out = malloc(len + 1);
        strcpy(out, empty);
        return out;
    }

    AsciiCanvas ac = ascii_new(width, height);
    tree_ascii_(t, &ac, 0, 0, padding);


    char* actual_out = malloc(len + 3);
    actual_out[0] = '\n';
    memcpy(actual_out + 1, ac.buffer, len);
    actual_out[len + 1] = '\n';
    actual_out[len + 2] = 0;

    ascii_free(ac);
    return actual_out;
}

TreeNode *search_tree_new_asdf(uint16_t item) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->item = item;
    n->left = NULL;
    n->right = NULL;
    return n;
}

TreeNode *t_3() {
    return search_tree_new_asdf(3);
}

TreeNode *t_6() {
    return search_tree_new_asdf(6);
}

TreeNode *t_8() {
    return search_tree_new_asdf(8);
}

TreeNode *t_3_6() {
    TreeNode *n = t_3();
    n->right = t_6();
    return n;
}

TreeNode *t_3_6_boring(uint16_t x) {
    TreeNode *n = t_3_6();
    n->item = x;
    n->right->item = x;
    return n;
}

TreeNode *t_3_8() {
    TreeNode *n = t_3();
    n->right = t_8();
    return n;
}

TreeNode *t_3_8_boring(uint16_t x) {
    TreeNode *n = t_3_8();
    n->item = x;
    n->right->item = x;
    return n;
}

TreeNode *t_6_3() {
    TreeNode *n = t_6();
    n->left = t_3();
    return n;
}

TreeNode *t_6_3_boring(uint16_t x) {
    TreeNode *n = t_6_3();
    n->item = x;
    n->left->item = x;
    return n;
}

TreeNode *t_6_8() {
    TreeNode *n = t_6();
    n->right = t_8();
    return n;
}

TreeNode *t_6_8_boring(uint16_t x) {
    TreeNode *n = t_6_8();
    n->item = x;
    n->right->item = x;
    return n;
}

TreeNode *t_8_3() {
    TreeNode *n = t_8();
    n->left = t_3();
    return n;
}

TreeNode *t_8_3_boring(uint16_t x) {
    TreeNode *n = t_8_3();
    n->item = x;
    n->left->item = x;
    return n;
}

TreeNode *t_8_6() {
    TreeNode *n = t_8();
    n->left = t_6();
    return n;
}

TreeNode *t_8_6_boring(uint16_t x) {
    TreeNode *n = t_8_6();
    n->item = x;
    n->left->item = x;
    return n;
}

TreeNode *t_3_6_8() {
    TreeNode *n = t_3_6();
    n->right->right = t_8();
    return n;
}

TreeNode *t_3_8_6() {
    TreeNode *n = t_3_8();
    n->right->left = t_6();
    return n;
}

TreeNode *t_6_3_8() {
    TreeNode *n = t_6_3();
    n->right = t_8();
    return n;
}

TreeNode *t_6_3_8_boring(uint16_t x) {
    TreeNode *n = t_6_3_8();
    n->item = x;
    n->left->item = x;
    n->right->item = x;
    return n;
}

TreeNode *t_6_8_3() {
    TreeNode *n = t_6_8();
    n->left = t_3();
    return n;
}

TreeNode *t_8_3_6() {
    TreeNode *n = t_8_3();
    n->left->right = t_6();
    return n;
}

TreeNode *t_8_6_3() {
    TreeNode *n = t_8_6();
    n->left->left = t_3();
    return n;
}

TreeNode *t_large() {
    TreeNode *a = search_tree_new_asdf(2);
    TreeNode *b = search_tree_new_asdf(5);
    TreeNode *c = search_tree_new_asdf(9);
    TreeNode *d = search_tree_new_asdf(8);
    d->left = b;
    d->right = c;
    TreeNode *e = search_tree_new_asdf(3);
    e->left = a;
    e->right = d;
    TreeNode *f = search_tree_new_asdf(33);
    TreeNode *g = search_tree_new_asdf(124);
    g->left = f;
    TreeNode *h = search_tree_new_asdf(24);
    h->right = g;
    TreeNode *i = search_tree_new_asdf(23);
    i->left = e;
    i->right = h;
    return i;
}

TreeNode *t_large_boring(uint16_t x) {
    TreeNode *a = search_tree_new_asdf(x);
    TreeNode *b = search_tree_new_asdf(x);
    TreeNode *c = search_tree_new_asdf(x);
    TreeNode *d = search_tree_new_asdf(x);
    d->left = b;
    d->right = c;
    TreeNode *e = search_tree_new_asdf(x);
    e->left = a;
    e->right = d;
    TreeNode *f = search_tree_new_asdf(x);
    TreeNode *g = search_tree_new_asdf(x);
    g->left = f;
    TreeNode *h = search_tree_new_asdf(x);
    h->right = g;
    TreeNode *i = search_tree_new_asdf(x);
    i->left = e;
    i->right = h;
    return i;
}

TreeNode *t_large_1() {
    TreeNode *n = t_large();
    n->left->left->left = search_tree_new_asdf(1);
    return n;
}

TreeNode *t_large_25() {
    TreeNode *n = t_large();
    n->right->right->left->left = search_tree_new_asdf(25);
    return n;
}

typedef struct TestData_
{
    TreeNode *before_insert;
    uint16_t item;
    uint16_t lt;
    TreeNode *boring;
} TestData;

static TestData test_cases[TEST_CASES];

char* render_exercise_1(TestData testcase)
{
    char *input = tree_ascii(testcase.before_insert);
    const char *x = format_int(testcase.item);
    
    int len = strlen("Setze alle Werte in folgenden Baum auf \n\n") + strlen(x) + strlen(input) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Setze alle Werte in folgenden Baum auf %s\n\n%s", x, input);
    free(input);
    free((char*) x);
    return str;
}

char* render_exercise_2(TestData testcase)
{
    char *input = tree_ascii(testcase.before_insert);
    const char *item = format_int(testcase.item);
    
    int len = strlen("Suche nach dem kleinsten Element größer als ") + strlen(item) + strlen(" in folgenden Baum:\n\n") + strlen(input) + 1;
    char *str = malloc(len);
    snprintf(str, len, "Suche nach dem kleinsten Element größer als %s in folgenden Baum:\n\n%s", item, input);
    free(input);
    free((char*) item);
    return str;
}

void assert_ost(Tester *t, TreeNode *expected, TreeNode *got, const char *context) {
    if (!search_tree_eq(expected, got)) {
        const char* s_expected = tree_ascii(expected);
        const char* s_got = tree_ascii(got);
        handle_assertion_failure(t, s_expected, s_got, context);
        free((char*) s_expected);
        free((char*) s_got);
    }
}

int main(int argc, char const *argv[]) {
    test_cases[0].before_insert = NULL;
    test_cases[0].item = 3;
    test_cases[0].lt = 3;
    test_cases[0].boring = NULL;

    test_cases[1].before_insert = t_3();
    test_cases[1].item = 3;
    test_cases[1].lt = 3;
    test_cases[1].boring = t_3();

    test_cases[2].before_insert = t_8();
    test_cases[2].item = 8;
    test_cases[2].lt = 8;
    test_cases[2].boring = t_8();

    test_cases[3].before_insert = t_3();
    test_cases[3].item = 8;
    test_cases[3].lt = 3;
    test_cases[3].boring = t_8();

    test_cases[4].before_insert = t_8();
    test_cases[4].item = 3;
    test_cases[4].lt = 3;
    test_cases[4].boring = t_3();

    test_cases[5].before_insert = t_3_6();
    test_cases[5].item = 8;
    test_cases[5].lt = 6;
    test_cases[5].boring = t_3_6_boring(8);

    test_cases[6].before_insert = t_3_8();
    test_cases[6].item = 6;
    test_cases[6].lt = 3;
    test_cases[6].boring = t_3_8_boring(6);

    test_cases[7].before_insert = t_6_3();
    test_cases[7].item = 8;
    test_cases[7].lt = 6;
    test_cases[7].boring = t_6_3_boring(8);

    test_cases[8].before_insert = t_6_8();
    test_cases[8].item = 3;
    test_cases[8].lt = 3;
    test_cases[8].boring = t_6_8_boring(3);

    test_cases[9].before_insert = t_8_3();
    test_cases[9].item = 6;
    test_cases[9].lt = 3;
    test_cases[9].boring = t_8_3_boring(6);

    test_cases[10].before_insert = t_8_6();
    test_cases[10].item = 3;
    test_cases[10].lt = 3;
    test_cases[10].boring = t_8_6_boring(3);

    test_cases[11].before_insert = t_6_3_8();
    test_cases[11].item = 6;
    test_cases[11].lt = 3;
    test_cases[11].boring = t_6_3_8_boring(6);

    test_cases[12].before_insert = t_6_3_8();
    test_cases[12].item = 3;
    test_cases[12].lt = 3;
    test_cases[12].boring = t_6_3_8_boring(3);

    test_cases[13].before_insert = t_6_3_8();
    test_cases[13].item = 8;
    test_cases[13].lt = 6;
    test_cases[13].boring = t_6_3_8_boring(8);

    test_cases[14].before_insert = t_large();
    test_cases[14].item = 1;
    test_cases[14].lt = 1;
    test_cases[14].boring = t_large_boring(1);

    test_cases[15].before_insert = t_large();
    test_cases[15].item = 2;
    test_cases[15].lt = 2;
    test_cases[15].boring = t_large_boring(2);

    test_cases[16].before_insert = t_large();
    test_cases[16].item = 8;
    test_cases[16].lt = 5;
    test_cases[16].boring = t_large_boring(8);

    test_cases[17].before_insert = t_large();
    test_cases[17].item = 25;
    test_cases[17].lt = 24;
    test_cases[17].boring = t_large_boring(25);

    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror "TEST_NAME".c -o "TEST_NAME".o -lm && ./"TEST_NAME".o");

    /* Aufgabe 1*/
    if(begin_exercise(&tester, "search_tree_boringify", "Aufgabe 1: Alle items überschreiben."))
    {
        for(int i = 0; i < TEST_CASES; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_1(test_cases[i]);
                TreeNode *got = search_tree_clone(test_cases[i].before_insert);
                search_tree_boringify(got, test_cases[i].item);
                assert_ost(&tester, test_cases[i].boring, got, args);
                free(args);
                search_tree_free(got);
            }
        }
    }

    /* Aufgabe 2*/
    if(begin_exercise(&tester, "search_tree_get_less_than", "Aufgabe 2: Suchen von nächstkleinerem Element."))
    {
        for(int i = 0; i < TEST_CASES; i++)
        {
            if(begin_testcase(&tester))
            {
                char *args = render_exercise_2(test_cases[i]);
                uint16_t got = search_tree_get_less_than(test_cases[i].before_insert, test_cases[i].item);
                assert_int(&tester, test_cases[i].lt, got, args);
                free(args);
            }
        }
    }

    for (int i = 0; i < TEST_CASES; i++) {
        search_tree_free(test_cases[i].before_insert);
        search_tree_free(test_cases[i].boring);
    }

    return wrap_up(&tester);
}
