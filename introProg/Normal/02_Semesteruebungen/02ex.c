/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 02ex_test.c -o 02ex_test.o -lm && ./02ex_test.o

Zum Testen mit valgrind (sehr zu empfehlen!):
clang -std=c11 -g -Wall -Werror 02ex_test.c -o 02ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./02ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Visualisieren Sie (wie auf dem Semesteraufgabenblatt 1 und 2) einen Sortieralgorithmus: Selectionsort.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void selection_sort(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    for (int i = 0; i < len - 1; i++)
    {
        uint8_t min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        uint8_t tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
        visualizer_append_array(v, arr);
    }
}

/*
Aufgabe 2:
Visualisieren Sie (wie auf dem Semesteraufgabenblatt 1 und 2) einen Sortieralgorithmus: Bubblesort.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void bubble_sort(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                uint8_t tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
        visualizer_append_array(v, arr);
    }
}
