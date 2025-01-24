/*
Zur Abgabe einen branch `iprg-b10` erstellen und pushen, in dem als einzige Datei die `10ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && ./10ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./10ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Implementieren Sie folgenden Algorithmus, um ein Array zu partitionieren:

- die `pivot_position` ist initial die erste Stelle im Array
- der Wert an der `pivot_position` ist das `pivot` Element
- solange es rechts der `pivot_position` Elemente gibt, die kleiner oder gleich `pivot` sind:
    - sei `i` die Position des rechtesten solchen Elements
    - rotiere die Werte an den Positionen `pivot_position`, `pivot_position + 1` und `i` nach rechts (siehe Testoutput)
    - inkrementiere die `pivot_position`

Nutzen Sie die `visualizer_append_array` Funktion (siehe `array_visualizer.h` bzw das Semesteraufgabenblatt 01) um den Algorithmus zu visualisieren. Und nutzen Sie die vom Testrunner erstellten Bilder zum Debuggen, und falls Ihnen das zu erwartende Verhalten unklar ist.

Imaginäre Bonuspunkte, wenn Ihre Implementierung in linearzeit läuft.

Tipp: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void visualize_partition(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    int pivot_position = 0;
    int right = len - 1;
    while (pivot_position < right)
    {
        if (arr[right] <= arr[pivot_position])
        {
            uint8_t tmp = arr[right];
            arr[right] = arr[pivot_position + 1];
            arr[pivot_position + 1] = arr[pivot_position];
            arr[pivot_position++] = tmp;
            visualizer_append_array(v, arr);
        }
        else
            right--;
    }
    return;
}

/*
Aufgabe 2:
Implementieren Sie Quicksort rekursiv, und visualisieren Sie den Algorithmus wie von den Tests verlangt.

Wählen Sie als Pivotelement stets das erste Element eines Teilarrays, und partitionieren Sie mit dem in Aufgabe 1 beschriebenen Algorithmus.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Visualisieren Sie außerdem das Array immer nachdem Sie ein Teilarray der Größe mindestens zwei partitioniert haben.
Tipp 3: Diese Funktion selbst lässt sich nicht sinnvoll rekursiv aufrufen. Schreiben Sie eine geeignete Funktion, und rufen Sie diese in `sort_quickly` auf.
*/
int this_could_be_much_shorter(Visualizer *v, uint8_t *arr, size_t len)
{
    int pivot_position = 0;
    int right = len - 1;
    while (pivot_position < right)
    {
        if (arr[right] <= arr[pivot_position])
        {
            uint8_t tmp = arr[right];
            arr[right] = arr[pivot_position + 1];
            arr[pivot_position + 1] = arr[pivot_position];
            arr[pivot_position++] = tmp;
        }
        else
            right--;
    }
    return pivot_position;
}
void sort(Visualizer *v, uint8_t *arr, size_t len, uint8_t *origin_arr)
{
    if (len < 2)
        return;
    int index = this_could_be_much_shorter(v, arr, len);
    visualizer_append_array(v, origin_arr);
    sort(v, arr, index, origin_arr);
    sort(v, arr + index + 1, len - index - 1, origin_arr);
    return;
}
void sort_quickly(Visualizer *v, uint8_t *arr, size_t len)
{
    visualizer_append_array(v, arr);
    sort(v, arr, len, arr);
    return;
}
