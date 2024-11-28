/*
Willkommen zum zehnten Aufgabenblatt vom Programmierkurs. Auf diesem Aufgabenblatt geht es um das Abgabesystem.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
 clang -std=c11 -g -Wall 10ex_test.c -o 10ex_test.o -lm && ./10ex_test.o
*/

/*
Aufgabe 1:

Geben Sie die drittkleinste ungerade natürliche Zahl zurück. Lesen Sie außerdem den Kommentar unterhalb dieser Aufgabe.
Tipp: gemeint ist die Zahl zwischen vier und sechs.
*/
int return_five() {
    return 5;
}

/*
Dieses Blatt war vergleichsweise einfach. Die gesparte Zeit sollen Sie damit verbringen,
das Abgabesystem für den Programmierkurs und den Rest von IntroProg zu verstehen.

Aus diversen, unvermeidlichen Gründen, ist das Abgabesystem etwas vertrackt.
Erklärt wird es in einem Video: https://isis.tu-berlin.de/mod/videoservice/view.php/cm/1942996/video/227289/view
Alternativ gibt es auch eine knappere schriftliche Erklärung: https://isis.tu-berlin.de/mod/resource/view.php?id=1942999

Sie können sich in den betreuten Arbeitszeiten Hilfe suchen, falls etwas nicht klappt.

Die Kernpunkte des Videos zur Wiederholung:

- Einmaliges Setup über den Isiskurs.
- Wir nutzen `git` für den Datentransfer: https://git-scm.com/
- Git ist ein komplexes Programm, aber Sie benötigen nur kleine, einfache Teile davon.
- Ein git *repository* is ein Verzeichnis, welcher von git zwischen mehreren Computern ausgetauscht werden kann.
- Sie haben *ein* git repository für *alle* ihre Abgaben.
- Git ermöglicht unterschiedliche Versionen des selben Repositories parallel zu verwalten, diese Versionen heißen *branches*.
- Wir nutzen einen branch pro Aufgabenblatt.
- Jede Abgabe (d.h., jeder branch) muss *exakt* eine Datei enthalten, sonst gehen Dinge schief.

Es folgen die Namen der Branches, die Sie für die Abgabe aller Aufgabenblätter des Programmierkurses benötigen:

| Blatt | Branch    | Datei  |
|-------|-----------|--------|
| 01    | pkurs-b01 | 01ex.c |
| 02    | pkurs-b02 | 02ex.c |
| 03    | pkurs-b03 | 03ex.c |
| 04    | pkurs-b04 | 04ex.c |
| 05    | pkurs-b05 | 05ex.c |
| 06    | pkurs-b06 | 06ex.c |
| 07    | pkurs-b07 | 07ex.c |
| 08    | pkurs-b08 | 08ex.c |
| 09    | pkurs-b09 | 09ex.c |
| 10    | pkurs-b10 | 10ex.c |

*/