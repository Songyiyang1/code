/*
Willkommen zum dritten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 03practice_test.c -o 03practice_test.o -lm && ./03practice_test.o

Auf diesem Blatt geht es unter anderem um:

- Funktionsaufrufe
- Die Canvas
*/

#include <stdio.h>
#include "03_canvas.h"

/*
Geben Sie '1' zurück falls 'x' gerade ist, und '0' falls 'x' ungerade ist.
*/
int is_even(int x)
{
    if (x % 2 == 0)
        return 1;
    return 0;
}

/*
Geben Sie '1' zurück falls 'x' ungerade ist, und '0' falls 'x' gerade ist.
Die Ziffer '2' soll nicht direkt in Ihrer Lösung vorkommen. Nutzen Sie stattdessen 'is_even'.
*/
int is_odd(int x)
{
    if (!is_even(x))
        return 1;
    return 0;
}

/*
Erstellen Sie folgende Zeichnung auf der Canvas:
(Jedes X symbolisiert einen schwarzen Pixel an den jeweiligen (x,y)-Koordinaten)

5---------
4-X-----X-
3---------
2-X-----X-
1--XXXXX--
0---------
/012345678

Nutzen Sie am besten eine Schleife für die Mundlinie.
*/
Canvas draw_smiley(Canvas c)
{
    for (int i = 2; i <= 4; i += 2)
    {
        canvas_set_black(c, 1, i);
        canvas_set_black(c, 7, i);
    }
    for (int i = 2; i <= 6; i++)
    {
        canvas_set_black(c, i, 1);
    }
    return c;
}

/*
Zeichnen Sie ein klassisches Schachbrettmuster, startend bei (0,0) mit Schwarz
*/
Canvas draw_chessboard(Canvas c)
{
    for (int i = 0; i < canvas_width(c); i++)
    {
        for (int j = 0; j < canvas_height(c); j++)
        {
            if (is_even(i + j))
            {
                canvas_set_black(c, i, j);
            }
        }
    }

    return c;
}

/*
Diese Funktion soll gefüllte Stufen zeichnen, welche von unten links anfangend nach rechts aufsteigen.
Jede Stufe soll eine Breite von `step_width` haben und eine Höhe von `step_height` (beide sind immer größer als null).
Für mehr Details schauen Sie einfach in das Test-Feedback für den ersten Testfall.
*/
Canvas i_told_you_about_stairs(Canvas c, int step_width, int step_height)
{
    int i = 0;
    int j = step_height;
    while (i < canvas_width(c) + step_width && j < canvas_height(c) + step_height) // die letzte Treppe könnte unvollständig sein
    {
        for (int x = i; x < canvas_width(c); x++)
        {
            for (int y = j - step_height; y < j; y++)
            {
                if (x < canvas_width(c) && y < canvas_height(c))
                    canvas_set_black(c, x, y);
            }
        }
        i += step_width;
        j += step_height;
    }

    /*
    for (int i = 0; i < canvas_width(c); i += step_width) // Abstand zum linken Rand
    {
        for (int j = step_height; j < canvas_height(c); j += step_height) //
        {
        }
    }
*/
    return c;
}