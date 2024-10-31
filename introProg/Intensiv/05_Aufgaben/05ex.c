/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o
*/

#include "05_canvas.h"
#include <stdio.h>
#include <math.h>

/*
Aufgabe 1a:
Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links liegender Pixel bei `(x, y)` ist.

_Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

*/
Canvas recursive_line(Canvas c, int x, int y, int width)
{
    if (width == 0)
        return c;
    if (x >= 0 && x < canvas_width(c) && y >= 0 && y < canvas_height(c))
        canvas_set_black(c, x, y);
    recursive_line(c, x + 1, y, width - 1);
    return c;
}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der Pixel der linken unteren Ecke liegt bei `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height)
{
    if (height == 0)
        return c;
    recursive_line(c, x, y, width);
    recursive_rectangle(c, x, y + 1, width, height - 1);
    return c;
}

/*
Aufgabe 2:
Die Fibonaccizahlen sind wie folgt definiert:

- die nullte Fibonaccizahl ist 1,
- die erste Fibonaccizahl ist ebenfalls 1, und
- jede weitere Fibonaccizahl ist die Summe der zwei vorigen Fibonaccizahlen.

Berechne die `n`-te Fibonaccizahl.
*/
int recursive(int x1, int x2, int n)
{
    if (n == 0)
        return x1 + x2;
    return recursive(x2, x1 + x2, n - 1);
}
int fibonacci(int n)
{
    int ans = 1;
    if (n > 1)
        ans = recursive(0, 1, n - 1);
    return ans;
}

/*
Aufgabe 3:
Implementieren Sie einen schwarzen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer (bereits bemalten) Canvas, soll die komplette
zusammenhängende Fläche aller Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden.
Zwei Pixel sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart sind. Jeder Pixel hat bis
zu vier direkte Nachbarn - die Diagonalen zählen nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im Headerfile der Canvas dokumentiert.
*/
Canvas bucket_fill(Canvas c, int x, int y)
{
    if (x < 0 || x >= canvas_width(c) || y < 0 || y >= canvas_height(c))
        return c;
    if (pixel_is_white(c, x, y))
    {
        canvas_set_black(c, x, y);
        bucket_fill(c, x + 1, y);
        bucket_fill(c, x - 1, y);
        bucket_fill(c, x, y + 1);
        bucket_fill(c, x, y - 1);
    }
    else
        return c;
    return c;
}
