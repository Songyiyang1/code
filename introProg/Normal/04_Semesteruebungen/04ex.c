/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 04ex_test.c -o 04ex_test.o -lm && ./04ex_test.o

Zum Testen mit valgrind (sehr zu empfehlen!):
clang -std=c11 -g -Wall -Werror 04ex_test.c -o 04ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./04ex_test.o
*/

#include <stdio.h>
#include <stdlib.h>

/*
In dieser Aufgabe arbeiten wir an doppelt verketteten Listen.

Das folgende Struct ist ein Node in einer doppelt verketteten Liste.
Dieses Struct dient als Implementierungsdetail.
Wer von außen mit einer DoublyLinkedList arbeitet,
bekommt Nodes nie direkt zu sehen.
*/
typedef struct Node {
    /* Der Datenwert, der in der Node gespeichert ist. */
    int data;
    /* Pointer auf die vorige Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *prev;
    /* Pointer auf die nächste Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *next;
} Node;

/* Eine doppelt verkettete Liste. */
typedef struct {
    /* Pointer auf die erste Node der Liste. */
    Node *head;
    /* Pointer auf die letzte Node der Liste. */
    Node *tail;
    /* Anzahl der Nodes in der Liste. */
    size_t size;
} DoublyLinkedList;

/*
Aufgabe 1: Einfügen am Anfang

Implementieren Sie die Funktion `prepend`, die einen neuen Knoten mit dem Wert `x` am Anfang der Liste einfügt.
*/
void prepend(DoublyLinkedList *list, int x) {
    // Platzhalter für Implementierung
}

/*
Aufgabe 2: Umkehren der Liste

Implementieren Sie die Funktion `reverse`, die die Reihenfolge der Knoten in der Liste umkehrt.
*/
void reverse(DoublyLinkedList *list) {
    // Platzhalter für Implementierung
}
