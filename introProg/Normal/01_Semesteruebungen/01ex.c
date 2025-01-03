/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 01ex_test.c -o 01ex_test.o -lm && ./01ex_test.o

Zum Testen mit valgrind (sehr zu empfehlen!):
clang -std=c11 -g -Wall -Werror 01ex_test.c -o 01ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./01ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe array_visualizer.h) vertraut.
Nutzen Sie die `visualizer_append_array` Funktion, um die Tests zum durchlaufen zu bringen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Jede weitere Zeile wird aus der Zeile davor durch eine einfache Modifikation gewonnen. Die Modifikation ist immer die gleiche.
*/
void warmup(Visualizer *v, uint8_t *arr, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        visualizer_append_array(v, arr);
        uint8_t tmp = arr[0];
        for (int j = 0; j < len - 1; j++)
            arr[j] = arr[j + 1];
        arr[len - 1] = tmp;
    }
}

/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void sort_it(Visualizer *v, uint8_t *arr, size_t len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        int j = i;
        uint8_t tmp = arr[j];
        while (j < len - 1 && tmp < arr[j + 1])
        {
            arr[j] = arr[j + 1];
            j++;
        }
        arr[j] = tmp;
        visualizer_append_array(v, arr);
    }
}
