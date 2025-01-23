#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "tree.h"
#include "ascii_canvas.h"

void tree_free(TreeNode *t) {
    if (t != NULL) {
        tree_free(t->left);
        tree_free(t->right);
        free(t);
    }
}

bool tree_eq(TreeNode *t1, TreeNode *t2) {
    if (t1 == NULL) {
        return t2 == NULL;
    } else if (t2 == NULL) {
        return false;
    } else {
        if (t1->item != t2->item) {
            return false;
        } else {
            return tree_eq(t1->left, t2->left) && tree_eq(t1->right, t2->right);
        }
    }
}

TreeNode *tree_clone(TreeNode *t) {
    if (t == NULL) {
        return NULL;
    } else {
        TreeNode *n = malloc(sizeof(TreeNode));
        n->item = t->item;
        n->left = tree_clone(t->left);
        n->right = tree_clone(t->right);
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

TreeNode *tree_new_asdf(uint16_t item) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->item = item;
    n->left = NULL;
    n->right = NULL;
    return n;
}

TreeNode *t_0() {
    return tree_new_asdf(0);
}

TreeNode *t_1() {
    return tree_new_asdf(1);
}

TreeNode *t_2() {
    return tree_new_asdf(2);
}

TreeNode *t_3() {
    return tree_new_asdf(3);
}

TreeNode *t_4() {
    return tree_new_asdf(4);
}

TreeNode *t_5() {
    return tree_new_asdf(5);
}

TreeNode *t_6() {
    return tree_new_asdf(6);
}

TreeNode *t_7() {
    return tree_new_asdf(7);
}

TreeNode *t_8() {
    return tree_new_asdf(8);
}

TreeNode *t_9() {
    return tree_new_asdf(9);
}

TreeNode *t_3_6() {
    TreeNode *n = t_3();
    n->right = t_6();
    return n;
}

TreeNode *t_3_8() {
    TreeNode *n = t_3();
    n->right = t_8();
    return n;
}

TreeNode *t_6_3() {
    TreeNode *n = t_6();
    n->left = t_3();
    return n;
}

TreeNode *t_6_8() {
    TreeNode *n = t_6();
    n->right = t_8();
    return n;
}

TreeNode *t_8_3() {
    TreeNode *n = t_8();
    n->left = t_3();
    return n;
}

TreeNode *t_8_6() {
    TreeNode *n = t_8();
    n->left = t_6();
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

TreeNode *t_6_3_8_2() {
    TreeNode *n = t_6_3_8();
    n->left->left = t_2();
    return n;
}

TreeNode *t_6_3_8_2_4() {
    TreeNode *n = t_6_3_8_2();
    n->left->right = t_4();
    return n;
}

TreeNode *t_6_3_8_2_4_7() {
    TreeNode *n = t_6_3_8_2_4();
    n->right->left = t_7();
    return n;
}

TreeNode *t_6_3_8_2_4_7_9() {
    TreeNode *n = t_6_3_8_2_4_7();
    n->right->right = t_9();
    return n;
}

TreeNode *t_6_3_8_2_4_7_9_1() {
    TreeNode *n = t_6_3_8_2_4_7_9();
    n->left->left->left = t_1();
    return n;
}

TreeNode *t_6_3_8_2_4_7_9_1_42_notasearchtree() {
    TreeNode *n = t_6_3_8_2_4_7_9_1();
    n->left->left->right = tree_new_asdf(42);
    return n;
}

TreeNode *t_2_2_2() {
    TreeNode *n = t_2();
    n->left = t_2();
    n->right = t_2();
    return n;
}

TreeNode *t_2_2_2_1a() {
    TreeNode *n = t_2_2_2();
    n->left->left = t_1();
    return n;
}

TreeNode *t_2_2_2_1b() {
    TreeNode *n = t_2_2_2();
    n->left->right = t_1();
    return n;
}

TreeNode *t_2_2_2_1c() {
    TreeNode *n = t_2_2_2();
    n->right->left = t_1();
    return n;
}

TreeNode *t_2_2_2_1d() {
    TreeNode *n = t_2_2_2();
    n->right->right = t_1();
    return n;
}

TreeNode *t_2_2_2_3a() {
    TreeNode *n = t_2_2_2();
    n->left->left = t_3();
    return n;
}

TreeNode *t_2_2_2_3b() {
    TreeNode *n = t_2_2_2();
    n->left->right = t_3();
    return n;
}

TreeNode *t_2_2_2_3c() {
    TreeNode *n = t_2_2_2();
    n->right->left = t_3();
    return n;
}

TreeNode *t_2_2_2_3d() {
    TreeNode *n = t_2_2_2();
    n->right->right = t_3();
    return n;
}

TreeNode *t_large() {
    TreeNode *a = tree_new_asdf(2);
    TreeNode *b = tree_new_asdf(5);
    TreeNode *c = tree_new_asdf(9);
    TreeNode *d = tree_new_asdf(8);
    d->left = b;
    d->right = c;
    TreeNode *e = tree_new_asdf(3);
    e->left = a;
    e->right = d;
    TreeNode *f = tree_new_asdf(33);
    TreeNode *g = tree_new_asdf(124);
    g->left = f;
    TreeNode *h = tree_new_asdf(24);
    h->right = g;
    TreeNode *i = tree_new_asdf(23);
    i->left = e;
    i->right = h;
    return i;
}

TreeNode *t_large_mirrored() {
    TreeNode *a = tree_new_asdf(2);
    TreeNode *b = tree_new_asdf(5);
    TreeNode *c = tree_new_asdf(9);
    TreeNode *d = tree_new_asdf(8);
    d->right = b;
    d->left = c;
    TreeNode *e = tree_new_asdf(3);
    e->right = a;
    e->left = d;
    TreeNode *f = tree_new_asdf(33);
    TreeNode *g = tree_new_asdf(124);
    g->right = f;
    TreeNode *h = tree_new_asdf(24);
    h->left = g;
    TreeNode *i = tree_new_asdf(23);
    i->right = e;
    i->left = h;
    return i;
}

TreeNode *t_large_boring(uint16_t x) {
    TreeNode *a = tree_new_asdf(x);
    TreeNode *b = tree_new_asdf(x);
    TreeNode *c = tree_new_asdf(x);
    TreeNode *d = tree_new_asdf(x);
    d->left = b;
    d->right = c;
    TreeNode *e = tree_new_asdf(x);
    e->left = a;
    e->right = d;
    TreeNode *f = tree_new_asdf(x);
    TreeNode *g = tree_new_asdf(x);
    g->left = f;
    TreeNode *h = tree_new_asdf(x);
    h->right = g;
    TreeNode *i = tree_new_asdf(x);
    i->left = e;
    i->right = h;
    return i;
}

TreeNode *t_large_1() {
    TreeNode *n = t_large();
    n->left->left->left = tree_new_asdf(1);
    return n;
}

TreeNode *t_large_25() {
    TreeNode *n = t_large();
    n->right->right->left->left = tree_new_asdf(25);
    return n;
}

#endif