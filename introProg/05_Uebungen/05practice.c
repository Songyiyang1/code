/*
Willkommen zum fünften Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des `cd` Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 05practice_test.c -o 05practice_test.o -lm && ./05practice_test.o

Auf diesem Blatt geht es um Rekursion.
*/

#include <stdio.h>
#include "05_canvas.h"

/*
Zeichne eine vertikale Linie der Höhe `height` mit unterstem Pixel an Position `(x, y)`.

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
Canvas vertical_line(Canvas c, int x, int y, int height) {
    return c;
}

/*
Wie viele Dezimalstellen hat `n` (`n` ist nicht negativ)?

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
int count_digits(int n) {
    return 0;
}

/*
Zeichne eine Pyramide: die unterste Zeile ist komplett schwarz, die zweitunterste Zeile lässt den ersten und letzten Pixel weiß, die drittunterste Zeile lässt die ersten zwei und die letzten zwei Pixel weiß, usw..

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
Canvas pyramid(Canvas c) {
    return c;
}

/*
Zeichne ein Rechteck der Breite `width` und der Höhe `height` mit einem Schachbrettmuster. Der Pixel der linken unteren Ecke liegt bei `(x, y)` und ist schwarz.

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
Canvas chessboard_rectangle(Canvas c, int x, int y, int width, int height) {
    return c;
}

/*
Der Binomialkoeffizient von `n` und `k` ("n über k"), mit `0 <= k <= n` ist wie folgt definiert:

- bin(n, 0) = 1, sonst
- bin(n, n) = 1, sonst
- bin(n, k) = bin(n - 1, k - 1) + bin(n - 1, k)

Berechne `bin(n, k)`.
*/
int binomial_coefficient(int n, int k) {
    return 0;
}

/*
Aufgabe 2:
Der *Sierpinski Carpet der Ordnung 0* ist ein einzelnes schwarzes Pixel.
Der *Sierpinski Carpet der Ordnung n+1* besteht aus acht Sierpinski Carpets der Ordnung n, angeordnet als drei-mal-drei
Quadrat dessen Mittelstück fehlt.

Beispiele (`X` stellt schwarze Pixel dar)
=========================================

Ordnung 0:

X

Ordnung 1:

XXX
X X
XXX

Ordnung 2:

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX

Siehe auch die Datei `05sierpinski.jpg`

Um in der nächsten Aufgabe den Sierpinski-Carpet auf die Canvas zeichnen zu können müssen Potenzen berechnet werden.
Implementieren Sie die Berechnung der Potenz einer nicht-negativen, ganzzahligen Basis `b` mit einem
nicht-negativen, ganzzahligen Exponenten `exp`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
int power(int b, int exp){
   return 0;
}

/*
Diese Funktion soll den Sierpinski Carpet der Ordnung `n` auf die Canvas zeichnen, mit unterer linker Ecke an Koordinate `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas sierpinski_carpet(Canvas c, int n, int x, int y){
    return c;
}

/*
Hinweis: Diese Aufgabe ist deutlich schwieriger als die vorangegangen, und ist als besondere Herausforderung gedacht :)
Eine *knifflige* Zahl ist eine Zahl deren einzige Dezimalziffern die Vier und die Sieben sind, und in der nie zwei
Siebenen aufeinander folgen.
Berechne die Anzahl der kniffligen Zahlen mit genau `n` Dezimalziffern.

Beispiel: die kniffligen Zahlen mit drei Dezimalziffern sind 444, 447, 474, 744, 747.
*/
int tricky_numbers(int n) {
    return 0;
}
