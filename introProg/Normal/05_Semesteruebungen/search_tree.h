#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H
#include <stdint.h>

/*
Ein Knoten in einem Suchbaum.

Wir repräsentieren Suchbäume durch pointer auf `Nodes` (der
leere Baum wird durch einen null-pointer repräsentiert).
*/
typedef struct TreeNode_ {
    uint16_t item; /* Der Wert, der in diesem Knoten gespeichert wird. */
    struct TreeNode_ *left; /* Der linke Teilbaum. */
    struct TreeNode_ *right; /* Der rechte Teilbaum. */
} TreeNode;

#endif