#ifndef HEIGHT_TREE_UTILS_H
#define HEIGHT_TREE_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "height_tree.h"
#include "ascii_canvas.h"
#include "String.h"

void height_tree_free(HeightTreeNode *t) {
    if (t != NULL) {
        height_tree_free(t->left);
        height_tree_free(t->right);
        free(t);
    }
}

bool height_tree_eq(HeightTreeNode *t1, HeightTreeNode *t2) {
    if (t1 == NULL) {
        return t2 == NULL;
    } else if (t2 == NULL) {
        return false;
    } else {
        if (t1->item != t2->item || t1->height != t2->height) {
            return false;
        } else if ((t1->parent == NULL && t2->parent != NULL) || (t1->parent != NULL && t2->parent == NULL)) {
            return false;
        } else if (t1->parent != NULL && (t1->parent->item != t2->parent->item)) {
            return false;
        } else {
            return height_tree_eq(t1->left, t2->left) && height_tree_eq(t1->right, t2->right);
        }
    }
}

HeightTreeNode *height_tree_clone_(HeightTreeNode *t, HeightTreeNode *clone_of_parent) {
    if (t == NULL) {
        return NULL;
    } else {
        HeightTreeNode *n = malloc(sizeof(HeightTreeNode));
        n->item = t->item;
        n->height = t->height;
        n->left = height_tree_clone_(t->left, n);
        n->right = height_tree_clone_(t->right, n);
        n->parent = clone_of_parent;
        return n;
    }
}

HeightTreeNode *height_tree_clone(HeightTreeNode *t) {
    return height_tree_clone_(t, NULL);
}

size_t height_tree_height(HeightTreeNode *t) {
    if (t == NULL) {
        return 0;
    } else {
        size_t left_height = height_tree_height(t->left);
        size_t right_height = height_tree_height(t->right);

        if (left_height > right_height) {
            return 1 + left_height;
        } else {
            return 1 + right_height;
        }
    }
}

size_t height_node_width(HeightTreeNode *t) {
    size_t p_width = t->parent == NULL ? 4 : ascii_width_u16(t->parent->item);
    /* The +2 counteracts the floorings. */
    return 4 /* [||] */ + ascii_width_u16(t->item) + ascii_width_size(t->height) + p_width;
}

size_t height_tree_width(HeightTreeNode *t, size_t padding /* num horizontal spaces between nodes*/) {
    if (t == NULL) {
        return 0;
    } else {
        size_t left_width = height_tree_width(t->left, padding);
        size_t right_width = height_tree_width(t->right, padding);

        size_t own_width = height_node_width(t) + padding;

        return left_width + padding + own_width + right_width;
    }
}

typedef struct DrawingInfo_ {
    uint16_t width;
    uint16_t docking_point; /* The midpoint of the root */
} DrawingInfo;

/* Draws the tree, with the top-left corner of its bounding box at (x, y) */
/* Returns the width of the drawing of this tree. */
DrawingInfo height_tree_ascii_(HeightTreeNode *t, AsciiCanvas *ac, uint16_t x, uint16_t y, uint16_t padding) {
    if (t == NULL) {
        DrawingInfo ret = { .width = 0, .docking_point = 0};
        return ret;
    }

    uint16_t label_width = height_node_width(t);
    DrawingInfo left_info = height_tree_ascii_(t->left, ac, x, y + 1, padding);
    uint16_t start_right = x + left_info.width + padding + label_width;
    DrawingInfo right_info = height_tree_ascii_(t->right, ac, start_right, y + 1, padding);
    uint16_t total_width = left_info.width + padding + label_width + padding + right_info.width;
    uint16_t own_docking_point = left_info.width + (2 * padding + label_width) / 2;

    // printf("width %d, height %d, item %d, left_width %d, label_width %d, right_width %d\n", ac->width, ac->height, t->item, left_info.width, label_width, right_info.width);

    /* prepare parent info */
    String parent_info = str_new();
    if (t->parent == NULL) {
        str_str(&parent_info, "NULL");
    } else {
        str_int(&parent_info, t->parent->item);
    }

    /* draw own label */
    char tmp = ascii_get(ac, x + left_info.width + padding + label_width, y);
    snprintf(ascii_get_str(ac, x + left_info.width + padding, y), label_width + 1, "[%d|%zu|%s]", t->item, t->height, parent_info.buf);
    ascii_set(ac, tmp, x + left_info.width + padding + label_width, y);

    str_free(parent_info);

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

char *height_tree_ascii(HeightTreeNode *t) {
    size_t padding = 1;
    
    size_t height = height_tree_height(t);
    size_t width = height_tree_width(t, padding) + 1;
    size_t len = height * (width + 1);

    if (height == 0) {
        char *empty = "\n(empty tree)\n";
        size_t len = strlen(empty);
        char *out = malloc(len + 1);
        strcpy(out, empty);
        return out;
    }

    AsciiCanvas ac = ascii_new(width, height);
    height_tree_ascii_(t, &ac, 0, 0, padding);


    char* actual_out = malloc(len + 3);
    actual_out[0] = '\n';
    memcpy(actual_out + 1, ac.buffer, len);
    actual_out[len + 1] = '\n';
    actual_out[len + 2] = 0;

    ascii_free(ac);
    return actual_out;
}

HeightTreeNode *height_tree_new_asdf(uint16_t item, HeightTreeNode *parent) {
    HeightTreeNode *n = malloc(sizeof(HeightTreeNode));
    n->item = item;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    n->parent = parent;
    return n;
}

#endif
