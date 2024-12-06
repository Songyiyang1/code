/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
In dieser Aufgabe arbeiten wir mit doppelt verketteten Listen, identisch zu denen von Blatt 04.

Das folgende Struct ist ein Node in einer doppelt verketteten Liste.
Dieses Struct dient als Implementierungsdetail.
Wer von außen mit einer DoublyLinkedList arbeitet,
bekommt Nodes nie direkt zu sehen.
*/
typedef struct Node
{
    /* Der Datenwert, der in der Node gespeichert ist. */
    int data;
    /* Pointer auf die vorige Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *prev;
    /* Pointer auf die nächste Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *next;
} Node;

/* Eine doppelt verkettete Liste. */
typedef struct
{
    /* Pointer auf die erste Node der Liste. */
    Node *head;
    /* Pointer auf die letzte Node der Liste. */
    Node *tail;
    /* Anzahl der Nodes in der Liste. */
    size_t size;
} DoublyLinkedList;

/*
Aufgabe 1: Sortieren

Sortieren Sie die gegebene Liste aufsteigend. Es kommen keine doppelten Datenwerte vor.
*/
void sort_list(DoublyLinkedList *list)
{
    Node *node = list->head;
    while (node)
    {
        printf("1");
        Node *tmp = node->prev;
        int tmp_num = node->data;
        while (tmp && tmp_num < tmp->data)
        {
            tmp->next->data = tmp->data;
            tmp = tmp->prev;
        }
        if (tmp)
            tmp->next->data = tmp_num;
        else
            list->head->data = tmp_num;
        node = node->next;
    }
    return;
}
