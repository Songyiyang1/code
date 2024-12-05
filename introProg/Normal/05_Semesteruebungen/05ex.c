/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Zum Testen mit valgrind (sehr zu empfehlen!):
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
Aufgabe 1a:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass `t` hinterher
wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t` stattdessen
unverändert bleiben.
Geben Sie zurück, ob der Baum modifiziert wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das Blatt wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/
bool search_tree_insert(TreeNode *t, uint16_t x) {
    return false;
}

/*
Aufgabe 1b:

Erstellen Sie einen neuen, absteigend sortieren Baum, der den gegebenen Suchbaum `t` spiegelt.

Nutzen Sie `malloc`, um die neuen Knoten zu erstellen. Der Testrunner wird sie wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/
TreeNode *search_tree_mirror(TreeNode *t) {
    return NULL;
}

/*
Aufgabe 2:

Geben Sie die Tiefe von `x` im Baum `t` zurück, oder `99999` falls `x` nicht in `t` vorkommt.
Die Laufzeit Ihrer Lösung soll proportional zur Höhe des Baumes sein, aber unabhängig
von der Gesamtzahl an Knoten.
*/
size_t search_tree_get_depth(TreeNode *t, uint16_t x) {
    return 0;
}

/*
Aufgabe 3a:

Geben Sie zurück, ob der Suchbaum `t` eine Zahl größer oder gleich `x` enthält.
*/
bool search_tree_has_gte(TreeNode *t, uint16_t x) {
    return 0;
}

/*
Aufgabe 3b:

Geben Sie zurück, ob der Suchbaum `t` eine Zahl enthält, die größer oder gleich `x` *und* echt kleiner als `y` ist.
*/
bool search_tree_has_in_range(TreeNode *t, uint16_t x, uint16_t y) {
    return false;
}

/*
Aufgabe 4:

Geben Sie die größte Zahl im Suchbaum `t` zurück, die (ganzzahlig) durch `x` teilbar ist.
`Geben Sie `0` zurück, falls keine solche Zahl existiert.
*/
uint16_t search_tree_greatest_divisible(TreeNode *t, uint16_t x) {
    return 0;
}
