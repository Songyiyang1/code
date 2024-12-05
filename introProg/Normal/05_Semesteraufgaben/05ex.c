/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Die Definition von Bäumen bzw. Knoten finden Sie in `./search_tree.h`
*/

/*
Aufgabe 1:

Ändern Sie alle im Baum `t` gespeicherten Werte auf `x`.
*/
void search_tree_boringify(TreeNode *t, uint16_t x)
{
    if (t)
    {
        t->item = x;
        if (!t->left && !t->right)
            return;
        if (t->left)
            search_tree_boringify(t->left, x);
        if (t->right)
            search_tree_boringify(t->right, x);
    }
}

/*
Aufgabe 2:
Geben Sie die größte Zahl im Suchbaum `t` zurück, welche echt kleiner als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten.
*/
uint16_t search_tree_get_less_than(TreeNode *t, uint16_t x)
{
    uint16_t ans = x;
    while (t)
    {
        if (t->item >= x)
            t=t->left; //nur im linken Baum moglich
        else
        {
            ans = t->item;//Notiere die bisherige beste Losung dann suche nach der nachste
            t = t->right;
        }
    }
    return ans;
}
