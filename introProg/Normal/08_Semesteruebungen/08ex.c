/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
bool descending_sphinx(Sphinx *s, size_t n) {
    return false;
}
