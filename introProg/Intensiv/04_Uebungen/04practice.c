/*
Willkommen zum vierten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 04practice_test.c -o 04practice_test.o -lm && ./04practice_test.o

Auf diesem Blatt geht es primär darum, komplexe Probleme erfolgreich anzugehen.
*/

#include <stdio.h>
#include "04_canvas.h"

/*
Nehme eine dreistellige Zahl, sortiere ihre Ziffern absteigend, und subtrahiere von dieser Zahl die Zahl die
sich aus den aufsteigend sortierten Ziffern ergibt.
Wiederhole, bis zwei mal in Folge die gleiche Zahl herauskommt.

Beispiel:

792 ~> 972 - 279 = 693
693 ~> 963 - 369 = 594
594 ~> 954 - 459 = 495
495 ~> 954 - 459 = 495

Gebe in dieser Funktion zurück, wie viele Schritte die dreistellige Eingabezahl 'n' braucht, um bei einer Zahl anzukommen,
bei der die sortiere-und-subtrahiere Prozedur wieder die Zahl selbst ausgibt.

Beispiele: 'kaprekar_count_steps(792) == 3', 'kaprekar_count_steps(693) == 2',
           'kaprekar_count_steps(594) == 1', 'kaprekar_count_steps(495) == 0'

Hinweis: Sollte die Eingabe 'x' kleiner als 100 sein (also weniger als 3 Dezimalstellen besitzen), sollte sie trotzdem
dreistellig behandelt werden, indem Nullen vorangesetzt werden. D.H. 64 ~> 640 - 046 = 594.
*/
int swap(int *a, int *b)
{
    int z;
    z = *a;
    *a = *b;
    *b = z;
    return 0;
}//VL6
int sort_max(int x)
{
    int x1 = x % 10;
    int x2 = (x / 10) % 10;
    int x3 = (x / 100) % 10;
    if (x1 > x2)
        swap(&x1, &x2);
    if (x2 > x3)
        swap(&x3, &x2);
    if (x1 > x2)
        swap(&x1, &x2);
    return x3 * 100 + x2 * 10 + x1;
}
int sort_min(int x)
{
    int x1 = x % 10;
    int x2 = (x / 10) % 10;
    int x3 = (x / 100) % 10;
    if (x1 < x2)
        swap(&x1, &x2);
    if (x2 < x3)
        swap(&x3, &x2);
    if (x1 < x2)
        swap(&x1, &x2);
    return x3 * 100 + x2 * 10 + x1;
}

int kaprekar_count_steps(int x)
{
    int count = 0;
    while (x != sort_max(x) - sort_min(x))
    {
        x = sort_max(x) - sort_min(x);
        count++;
    }

    return count;
}

/*
Färbe alle Pixel (mit den Koordinaten '(x, y)') auf dem Canvas schwarz, für welche die sortiere-und-subtrahiere Aktion
von 'x' die Zahl 'y' ergibt.

Bonus: Gibt es ein Muster, dass man ausnutzen kann um 'kaprekar_count_steps' effizienter zu implementieren als
alle Schritte durchzuführen?
*/
Canvas plot_kaprekar(Canvas c)
{
    for (int i = 0; i < canvas_width(c); i++)
    {
        int j = sort_max(i) - sort_min(i);
        if (j < canvas_height(c))
            canvas_set_black(c, i, j);
    }

    return c;
}
