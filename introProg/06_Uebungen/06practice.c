/*
Willkommen zum sechsten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 06practice_test.c -o 06practice_test.o -lm && ./06practice_test.o

Auf diesem Blatt geht es um Typen.
*/

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include "06_canvas.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct RGB_
{
    float r;
    float g;
    float b;
} RGB;

/*
Färben Sie alle Pixel, deren x-Koordinate kleiner gleich ihrer y-Koordinate sind mit der Farbe 'color1', und alle anderen
Koordinaten mit der Farbe 'color2'.
*/
Canvas right_triangle(Canvas c, RGB color1, RGB color2)
{
    for (int i = 0; i < canvas_width(c); i++)
    {
        for (int j = 0; j < i; j++)
        {
            canvas_set_r(c, i, j, color2.r);
            canvas_set_g(c, i, j, color2.g);
            canvas_set_b(c, i, j, color2.b);
        }
        for (int j = i; j < canvas_height(c); j++)
        {
            canvas_set_r(c, i, j, color1.r);
            canvas_set_g(c, i, j, color1.g);
            canvas_set_b(c, i, j, color1.b);
        }
    }
    return c;
}

/*
Mischen Sie 'color1' und 'color2', indem Sie jeden Farbkanal auf den Mittelpunkt zwischen den Werten der entsprechenden
Farbkanäle von 'color1' und 'color2' setzen.
*/
RGB mix_colors(RGB color1, RGB color2)
{
    color1.r = (color1.r + color2.r) / 2;
    color1.g = (color1.g + color2.g) / 2;
    color1.b = (color1.b + color2.b) / 2;
    return color1;
}

/*
Färben Sie alle Pixel wie in der 'right_triangle'-Übung, aber benutzen Sie die Mischung zwischen 'color1' und 'color2' für
die Pixel der direkt aneinander grenzenden Kanten der entstehenden Dreiecke.
*/
Canvas antialiased_right_triangle(Canvas c, RGB color1, RGB color2)
{
    for (int i = 0; i < canvas_width(c); i++)
    {
        for (int j = 0; j < i; j++)
        {
            canvas_set_r(c, i, j, color2.r);
            canvas_set_g(c, i, j, color2.g);
            canvas_set_b(c, i, j, color2.b);
        }
        RGB color3 = mix_colors(color1, color2);
        canvas_set_r(c, i, i, color3.r);
        canvas_set_g(c, i, i, color3.g);
        canvas_set_b(c, i, i, color3.b);
        if (i - 1 >= 0)
        {
            canvas_set_r(c, i, i - 1, color3.r);
            canvas_set_g(c, i, i - 1, color3.g);
            canvas_set_b(c, i, i - 1, color3.b);
        }

        for (int j = i + 1; j < canvas_height(c); j++)
        {
            canvas_set_r(c, i, j, color1.r);
            canvas_set_g(c, i, j, color1.g);
            canvas_set_b(c, i, j, color1.b);
        }
    }
    return c;
}

/*
Berechnen Sie das 627-fache von 'n', aber geben Sie '-1' zurück, falls 'n' negativ ist, oder falls die Lösung nicht
in einem 'int16_t' dargestellt werden kann.
*/
int16_t times627(int16_t n)
{
    int16_t a = n * 627;
    if (n < 0)
        return -1;
    else if (a < 0)
        return -1;
    else
        return n * 627;
}

/*
Berechnen Sie den Winkel (in Grad) zwischen der Linie von Punkt (0, 0) nach Punkt (x, y) und der Linie von Punkt
(0, 0) nach Punkt (1, 0), also der X-Achse.

Hinweis: Wir haben weder beigebracht wie die Mathematik dafür funktioniert, noch wie die benötigten Funktionen
im <math.h> Header lauten. Beides lässt sich im Web suchen oder mit KomillitonInnen besprechen.
Das ist explizit gewünscht, nur abzuschreiben ohne selber nachzudenken wäre schade.
*/
float compute_angle(float x, float y)
{
    // Winkel soll mit arctan(y/x) berechnen werden
    // Laut Internet soll der Wert Double sein
    double angle = atan2(y , x); // AH ist in RAD und atan() funktioniert nicht weil die winkel da kann negativ sein
    angle = angle * 360 / 2 / M_PI;
    return angle;
}