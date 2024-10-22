/*
Willkommen zum achten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des `cd` Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 08practice_test.c -o 08practice_test.o -lm && ./08practice_test.o

Auf diesem Blatt geht es um Arrays.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/*
Geben Sie die kleinste Zahl im Eingabearray zurück.
*/
uint16_t get_minimum(uint16_t numbers[], size_t numbers_len) {
    return 0;
}

/*
Geben Sie einen Pointer auf das erste Vorkommen der Zahl `7` im Eingabearray zurück, oder `NULL` falls die `7`
nicht vorkommt.
*/
uint16_t *find_seven(uint16_t numbers[], size_t numbers_len) {
    return numbers;
}

/*
Schreiben Sie einen Countdown in das gegebene Array `numbers`.
Bespiel: ist `numbers_len` drei, sollte das Array am Ende die Werte 2, 1, und 0 enthalten (in dieser Reihenfolge).
*/
void countdown(uint16_t numbers[], size_t numbers_len) {
    return;
}

/*
Wir können zweidimensionale Arrays bequem als eindimensionale Arrays darstellen, indem wir
die Zellen durchnummerieren.
Beispiel:

+-+-+-+
|3|4|5|            +-+-+-+-+-+-+
+-+-+-+ entspricht |0|1|2|3|4|5|
|0|1|2|            +-+-+-+-+-+-+
+-+-+-+

Wie können zweidimensionale Koordinaten in eindimensionale Koordinaten umgerechnet werden?
z.B. addressiert die 2d-Koordinate (0, 0) die Zelle 0, (1, 0) addressiert Zelle 1, (2, 0) Zelle 2, (0, 1) Zelle 3,
(1, 1) Zelle 4, und (2, 1) Zelle 5.

Diese Funktion erhält ein eindimensionales Array `arr`, welches ein 2d Array der Breite `width` und Höhe `height`
repräsentiert.
Geben Sie den Wert an der Koordinate (x, y) zurück.
*/
uint16_t get_value(uint16_t arr[], size_t width, size_t height, size_t x, size_t y) {
    return 0;
}

/*
Ein _lateinisches Quadrat_ ist ein Quadrat, in dem jeder Wert innerhalb seiner Zeile und seiner Spalte nur ein mal vorkommt.
Ist das gegebene Array `arr` ein lateinisches Quadrat der Seitenlängen `length`?
Hinweis: die Transformation ins Zweidimensionale ist wie in der Voraufgabe.
*/
bool is_latin_square(uint16_t arr[], size_t length) {
    return 0;
}

/*
Ein _magisches Quadrat_ ist ein Quadrat, in dem die Summe der Werte in jeder Zeile, Spalte, und der beiden großen
Diagonalen, identisch ist.
Ist das gegebene Array `arr` ein magisches Quadrat der Seitenlängen `length`?
Hinweis: die Transformation ins Zweidimensionale ist wie in der Voraufgabe.
*/
bool is_magic_square(uint16_t arr[], size_t length) {
    return 0;
}