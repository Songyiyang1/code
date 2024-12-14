/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void merge(Visualizer *v, uint8_t *arr, int l, int mid, int r)
{
    uint8_t *tmp = (uint8_t *)malloc((r - l + 1) * sizeof(uint8_t)); // Array B
    int i = l;
    int j = mid + 1;
    int b = 0;
    while (i <= mid && j <= r)
    {
        if (arr[i] <= arr[j])
            tmp[b++] = arr[i++];
        else
            tmp[b++] = arr[j++];
    }
    while (i <= mid)
        tmp[b++] = arr[i++];
    while (j <= r)
        tmp[b++] = arr[j++];
    for (int k = l; k <= r; k++)
        arr[k] = tmp[k - l];
    free(tmp);
    visualizer_append_array(v, arr);
}
void mergeSort(Visualizer *v, uint8_t *arr, size_t len)
{
    int step = 1;
    while (step < len)
    {
        int l = 0;
        while (l <= len - step)
        {
            int mid = l + step - 1;
            if (mid > len - 1) // unnoetig???
                mid = len - 1;
            int r = l + 2 * step - 1;
            if (r > len - 1)
                r = len - 1;
            merge(v, arr, l, mid, r);
            l += 2 * step;
        }
        step *= 2;
    }
}
void sort_it(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    mergeSort(v, arr, len);
}
