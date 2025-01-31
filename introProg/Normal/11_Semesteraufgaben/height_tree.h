#ifndef HEIGHT_TREE_H
#define HEIGHT_TREE_H
#include <stdint.h>
#include <stddef.h>

/*
Ein Knoten in einem Baum von `uint16_t`s.
Jeder Knoten speichert die Höhe des Teilbaums, dessen Elternknoten er ist.
Weiterhin enthält jeder Knoten einen Elternpointer, der Elternpointer der Wurzel ist `NULL`.

Wir repräsentieren Bäume durch pointer auf `HeightTreeNode`s (der
leere Baum wird durch einen null-pointer repräsentiert).
*/
typedef struct HeightTreeNode_ {
    uint16_t item; /* Der Wert, der in diesem Knoten gespeichert wird. */
    size_t height; /* Die Höhe von diesem Baum, beispielsweise `1` für ein Blatt. */
    struct HeightTreeNode_ *left; /* Der linke Teilbaum. */
    struct HeightTreeNode_ *right; /* Der rechte Teilbaum. */
    struct HeightTreeNode_ *parent; /* Der Elternknoten. */
} HeightTreeNode;

#endif