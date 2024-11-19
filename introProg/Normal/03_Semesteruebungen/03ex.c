/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 03ex_test.c -o 03ex_test.o -lm && ./03ex_test.o

Zum Testen mit valgrind (sehr zu empfehlen!):
clang -std=c11 -g -Wall -Werror 03ex_test.c -o 03ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./03ex_test.o
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
Dieses struct ist identisch zu dem aus den Pflichthausaufgaben.

Eine Sequenz von Zahlen, die beliebig wachsen kann.
Die Elemente werden hintereinander in einem dynamisch allokierten Array auf dem Heap gespeichert.
*/
typedef struct Sequence_ {
    uint16_t *data; /* Alle aktuellen Elemente, hintereinander im Speicher. */
    size_t len; /* Wie viele Elemente enthält die Sequenz gerade? Die ersten `len` vielen Einträge in `data` haben Bedeutung, die restlichen dürfen Unfug sein. */
    size_t capacity; /* Die Größe des aktuellen `data` Arrays. */
} Sequence;

/*
Aufgabe 1: Filtern

Entfernen Sie aus der gegebenen Sequenz alle ungeraden Zahlen.
Beispiel: aus [0, 1, 2, 3, 4] soll [0, 2, 4] werden.
*/
void seq_remove_odds(Sequence *seq) {
    for(int i=0;i<seq->len;i++){
        
    }
    return;
}

/*
Aufgabe 2: Einsen anhängen

Implementieren Sie eine Funktion, die `n` viele Einsen an das Ende der Sequenz hinzufügt.
Wenn die Kapazität des Arrays nicht ausreicht, ersetzen Sie das Array mit einem neuen Array von genau ausreichender Größe.
Kopieren Sie die alten Daten in das neue Array, fügen Sie das neue Element ein, und geben Sie den Speicher vom alten Array frei.
Aktualisieren Sie die `len` und `capacity` Felder.

Achtung: unser Testcode wird bei Bedarf `free` für von Ihnen allokierte Arrays aufrufen. Falls Ihr Code fehlerhaft ist, kann das zu Abstürzen führen.
*/
void seq_append_ones(Sequence *seq, size_t n) {
    return;
}
