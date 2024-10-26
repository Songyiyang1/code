/*
Willkommen zum neunten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
 clang -std=c11 -g -Wall 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Um den Code mit `valgrind` auszuführen (unten erläutert), führen Sie den folgenden Befehl aus:
 clang -std=c11 -g -Wall 09ex_test.c -o 09ex_test.o -lm && valgrind ./09ex_test.o

Für Mac User (entweder valgrind über homebrew installieren, oder folgender Befehl):
Um den Code mit `fsanitize` auszuführen (gleiche Funktionalität wie valgrind), führen Sie die folgenden Befehle aus:
 Für Zugriffsfehler: clang -std=c11 -g -Wall 09ex_test.c -o 09ex_test.o -lm -fsanitize=address && ./09ex_test.o
 Für Speicherfehler: clang -std=c11 -g -Wall 09ex_test.c -o 09ex_test.o -lm -fsanitize=memory && ./09ex_test.o

Wir können für MacOS keinen zusätzlichen Support garantieren. Nutzen Sie idealerweise ein UNIX-Terminal, zum Beispiel
über die Rechner an der Universität, Dual-Boot, etc...
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1a:
Geben Sie einen gültigen Pointer auf den gleichen Wert wie `x` zurück.
Tipp: Ein Pointer direkt auf `x` ist nicht gültig. Warum?
*/
uint32_t *return_pointer(uint32_t x)
{

    uint32_t *p;
    p = (uint32_t *)malloc(sizeof(x));
    *p = x;
    return p;
    /*uint32_t* p=&x;
    return p;*/
}

/*
Aufgabe 1b:
Geben Sie den Wert zurück, auf den der Pointer `x` zeigt, und rufen Sie `free` auf `x` auf.
Tipp: Nach dem Aufruf von `free` darf der Pointer nicht mehr dereferenziert werden.
*/
uint32_t free_pointer(uint32_t *x)
{
    uint32_t tmp = *x;
    free(x);
    return tmp;
}

/*
Eine Einführung in Valgrind

Wenn man ein Progamm ausführt, weist das Betriebssystem ihm eine bestimmte Speicherregion zu. Um sicherzugehen,
dass ein Programm nicht in den Speicher eines anderen Programms eindringt, werden alle Speicherzugriffe vom
Betriebssystem überwacht. Sollte unser Programm einen Fehltritt wagen, wird es sofort vom Betriebssystem terminiert.
Die Konsole spuckt dann eine Fehlermeldung aus, in der Regel "Segmentation Fault (core dumped)" oder "double free or corruption".

Dies kann nur passieren, wenn der Quellcode des Programms unerlaubte Dinge tut, wie z.B. die Grenzen eines Arrays zu
überschreiten. Aber nicht jeder solcher Fehler wird vom Betriebssystem erkannt, beispielsweise ein ungültiger Arrayzugriff,
der *nicht* in die Speicherregion eines anderen Programms führt.

Valgrind ist ein externes Programm, welchem wir unseren Code übergeben können, um zu überprüfen ob dieser zur Laufzeit
unzulässige Speicherzugriffe ausführt, oder den Speicher unzureichenend verwaltet. Im Gegensatz zum Betriebssystem,
versucht valgrind, _alle_ Fehler zu erkennen. Außerdem bietet es weitaus präzisere und hilfreichere Fehlermeldungen.

Wir empfehlen Ihnen, sich mit valgrind vertraut zu machen. Es gibt viele Fehler die ohne valgrind
schwer bis unmöglich zu finden und zu beheben sind. Auf unseren Servern läuft valgrind im gesamten Semester bei vielen
Tests mit.
Dass bei Ihnen die Fehler ohne valgrind eventuell nicht sichtbar sind, ist keine Garantie, dass es keine Fehler gibt!

Valgrind läuft auf allen gängigen UNIX-Systemen und ist auf den meisten sogar vorinstalliert (so zum Beispiel in Ubuntu
auf den Uni-Rechnern). Für Windows-User kann valgrind im Windows-Subsystem for Linux (WSL) installiert werden.
Auf Macs kann es schwierig sein, valgrind auszuführen. Dort können alternativ die `fsanitize` Optionen des `clang` Compilers
genutzt werden (am Anfang dieser Datei stehen dazu mehr Informationen).

Um valgrind auszuführen, schreiben wir als Erstes `valgrind` in die Konsole, und übergeben dann wie gewöhnlich unseren
Programmaufruf. Im Aufruf von oben sieht das folgendermaßen aus:
 clang -std=c11 -g -Wall 09ex_test.c -o 09ex_test.o -lm && valgrind ./09ex_test.o
Nehmen wir nur den zweiten Teil
 valgrind ./09ex_test.o
sehen wir, dass wir im Endeffekt valgrind einfach vor unseren üblichen Programmaufruf schreiben können. Dadurch wird
unser Programm in einer speziellen Umgebung innherhalb vom valgrind-Programm ausgeführt, welche alle Speicherzugriffe
und Allokationen analysiert.

Ein üblicher valgrind Fehler sieht so aus (Der Fehler ist fiktiv):
1.    Invalid read of size 4
2.        at 0x40B07FF4: return_pointer (09ex.c:35)
3.        at 0x40AC751B: main (09ex_test.c:156)
4.    Address 0xBFFFF0E0 is 0 bytes after a block of size 12 alloc`d
5.        at 0x4C2EB6B: malloc (vg_replace_malloc.c:299)
6.        by 0x40AA639: main (09ex.c:31)

In der ersten Zeile bekommen wir bereits viele nützliche Informationen. Ob wir beim Lesen oder Schreiben des Speichers
einen unzulässigen Zugriff gemacht haben, und wie viele Bytes groß dieser Zugriff war. Das gibt uns erste Rückschlüsse
nach welcher Art Fehler wir suchen sollten.
Die nächsten Zeilen beinhalten einen `Stacktrace`, eine Zurückverfolgung, wie die Funktion die den Fehler ausgelöst hat
aufgerufen wurde. Man liest diesen am besten von unten nach oben. Die Speicheradressen am Anfang sind in der Regel für
uns uninteressant.
 main (09ex_test.c:156)
Die Funktion (`main`), gefolgt von der Datei (`09ex_test.c`) gefolgt von der Zeile, getrennt von einem Doppelpunkt (`156`)
In Zeile 156 wird also eine weitere Funktion aufgerufen, welche im Stacktrace direkt *darüber* steht.
 return_pointer (09ex.c:35)
Wenn das die oberste Funktion im Stacktrace ist, gibt die Line (hier `35`) die Codezeile an, die den Fehler ausgelöst hat.

Mit diesen Informationen wissen wir jetzt schon mal, dass wir in Zeile 35 der 09ex.c Datei 4 Bytes Speicher lesen, die wir
nicht lesen dürften.
Die 4. Zeile gibt uns weitere Hinweise, was genau passiert ist.
 Address <Diese Nummer ist uns egal> is 0 bytes after a block of size 12 alloc`d

0 bytes after block X bedeutet, dass der Zugriff direkt *hinter* (und damit *außerhalb*) eines gültigen Speicherbereichs ist.

Dieses Aufgabenblatt ist etwas abgespeckter, damit Sie mehr Zeit haben valgrind aufzusetzen, und sich damit vertraut zu
machen (es wird Ihnen im ganzen verbleibenden Semester immens helfen!).
*/

/*
Aufgabe 1c:
Eventuell haben Sie die Aufgaben 1a und 1b bereits gelöst, wenn Sie das hier lesen. Versuchen Sie, die Hinweise der
Aufgabenstellungen einmal absichtlich zu ignorieren. Führen sie den fehlerhaften Code sowohl mit als auch ohne valgrind aus,
und versuchen sie, die Fehlermeldungen von Valgrind zu verstehen.
(Diese Aufgabe wird nicht bewertet)
*/

/*
Für die folgenden Aufgaben benötigen wir wieder die Pancakes von Aufgabenblatt 07:
*/

/*
Ein ordentlicher Pfannkuchenhaufen hat mehrere Schichten, und zwar aus Obst, Schlagsahne, oder tatsächlichem Teigfladen.
*/
typedef enum Layer_
{
    Fruit,
    Cream,
    ActualPancake
} Layer;

/*
Ein Pfannkuchenhaufen besteht aus einer Schicht, auf der möglicherweise ein weiterer Pfannkuchenhaufen liegt:
*/
typedef struct PileOfPancakes_
{
    Layer layer;                            /* Die unterste Schicht. */
    struct PileOfPancakes_ *further_layers; /* Weitere Schichten, oder `null` falls keine mehr folgen. */
} PileOfPancakes;

/*
Aufgabe 2a:
Geben Sie einen Pfannkuchenhaufen zurück, dessen einzige Schicht eine Fruchtschicht ist.
*/
PileOfPancakes pure_fruit()
{
    PileOfPancakes p = {.layer = Fruit, .further_layers = NULL};
    return p;
}

/*
Aufgabe 2b:
Geben Sie einen gültigen Pointer auf einen Pfannkuchenhaufen zurück, dessen einzige Schicht eine Fruchtschicht ist.
Der Testcode wird `free` auf diesem Pointer aufrufen.
*/
PileOfPancakes *pure_fruit_ptr()
{
    PileOfPancakes *pancakep = (PileOfPancakes *)malloc(sizeof(PileOfPancakes));
    PileOfPancakes pancake = {.layer = Fruit, .further_layers = NULL};
    *pancakep = pancake;
    return pancakep;
}

/*
Aufgabe 2c:
Geben Sie einen gültigen Pointer auf einen zweischichtigen Pfannkuchenhaufen zurück, dessen unterste Schicht ein tatsächlicher Teigfladen ist, auf dem eine einzelne Fruchtschicht liegt.
Der Testcode wird `free` auf diesem Pointer aufrufen.
*/
PileOfPancakes *fruit_crepe_ptr()
{
    PileOfPancakes *pancake = (PileOfPancakes *)malloc(sizeof(PileOfPancakes));
    PileOfPancakes pancake1 = {.layer = ActualPancake, .further_layers = pure_fruit_ptr()};
    *pancake = pancake1;
    return pancake;
}

/*
Aufgabe 2d:
Erstellen Sie einen Pfannkuchen aus genau `n` Schichten Teigfladen (`n` ist mindestens 1).
*/
PileOfPancakes mille_crepes(uint32_t n)
{
    if (n == 1)
    {
        PileOfPancakes p = {.layer = ActualPancake, .further_layers = NULL};
        return p;
    }
    PileOfPancakes *pancake = (PileOfPancakes *)malloc(sizeof(PileOfPancakes));
    *pancake = mille_crepes(n - 1);
    PileOfPancakes p = {.layer = ActualPancake, .further_layers = pancake};
    return p;
}

/*
Bisher haben wir `malloc` immer mit `sizeof(SomeType)` aufgerufen, aber prinzipell kann man beliebige Zahlen
als Argument übergeben. Besonders interessant sind hier Aufrufe der Form `malloc(n * sizeof(someType))`.
So ein Aufruf allokiert hintereinander genug Speicher für `n` viele Werte vom Typ `someType`.
Das sollte vetraut klingen - ein Array der Länge `n` für Werte vom Typ `someType` ist nichts anderes.
Und während die Länge eines Arrays statisch im Code festgelegt sein muss, kann die Länge bei malloc variabel gewählt werden.

Beispielcode:

uint8_t* dynamic_array = malloc(x * sizeof(uint8_t));
dynamic_array[3] = 17; // Hoffentlich ist x mindestens vier, ansonsten ist das hier ein Out-of-Bounds Zugriff
dynamic_array[y - 1] = 42; // Hoffen wir, dass y nicht 0 ist, da es sich sonst auch um einen Out-of-Bounds Zugriff handelt.
free(dynamic_array);

Als weiteres Beispiel verwenden wir das RGB struct aus vorherigen Aufgabenblättern um ein Array zu erstellen und zu füllen.
Mit einem bisschen cleveren Umrechnen machen wir so aus einem Array ein zweidimensionales Bild!
Das Geheimnis ist gelüftet! Unser Canvas, zumindest das Bild selbst, ist bloß ein großes Array voller Zahlenwerte.

RGB *image = malloc((width * height) * sizeof(RGB));
for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
        image[(i*height)+j] = {.r = 0.5, .g = 0.5, .b = 0.5};
    }
}
*/

/*
Aufgabe 3:
Erstellen Sie mit `malloc` ein `uint16_t` Array der Länge `x`, füllen Sie es mit den ersten `x` Quadratzahlen, und
geben Sie es zurück.
Hinweis: Wir starten bei `1`.
*/
uint16_t *create_dynamic_array(size_t x)
{
    uint16_t *q = (uint16_t *)malloc(x * sizeof(uint16_t));
    for (int i = 0; i < x; i++)
        *(q + i) = (i + 1) * (i + 1);
    return q;
}
