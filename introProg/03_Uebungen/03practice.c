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
int is_even(int x) {
    return 0;
}

/*
Geben Sie '1' zurück falls 'x' ungerade ist, und '0' falls 'x' gerade ist.
Die Ziffer '2' soll nicht direkt in Ihrer Lösung vorkommen. Nutzen Sie stattdessen 'is_even'.
*/
int is_odd(int x) {
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
Canvas draw_smiley(Canvas c) {
    return c;
}

/*
Zeichnen Sie ein klassisches Schachbrettmuster, startend bei (0,0) mit Schwarz
*/
Canvas draw_chessboard(Canvas c) {
    return c;
}

/*
Diese Funktion soll gefüllte Stufen zeichnen, welche von unten links anfangend nach rechts aufsteigen.
Jede Stufe soll eine Breite von `step_width` haben und eine Höhe von `step_height` (beide sind immer größer als null).
Für mehr Details schauen Sie einfach in das Test-Feedback für den ersten Testfall.
*/
Canvas i_told_you_about_stairs(Canvas c, int step_width, int step_height) {
    return c;
}