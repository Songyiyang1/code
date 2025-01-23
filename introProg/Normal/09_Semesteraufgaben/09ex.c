/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein linksvollständiger Binärbaum `t`, geben Sie zurück, ob `t` die min-heap Eigenschaft erfüllt.
*/
bool is_min_heap(TreeNode *t)
{
    if (t == NULL)
        return true;
    if (is_min_heap(t->left) && is_min_heap(t->right))
    {
        uint16_t left = UINT16_MAX;
        uint16_t right = UINT16_MAX;
        if (t->left != NULL)
            left = t->left->item;
        if (t->right != NULL)
            right = t->right->item;
        if (left >= t->item && right >= t->item)
            return true;
    }
    return false;
}

/*
Aufgabe 2:

Gegeben ein Array `arr`, geben Sie den zugehörigen linksvollständigen Binärbaum zurück.
*/
void dfs(TreeNode *t, Array array, int index)
{
    if(index>=array.len) return;
    t->item=array.arr[index];
    dfs(t->left,array,2*index+1);
    dfs(t->right,array,2*index+2);
    return;
}
TreeNode *array_to_tree(Array arr)
{
    TreeNode *t=(TreeNode*)malloc(sizeof(TreeNode)*arr.len);
    dfs(t,arr,0);
    return t;
}