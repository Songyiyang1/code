#ifndef SPHINX_H
#define SPHINX_H

#include <stddef.h>
#include <stdint.h>

/*
Eine Sphinx, die sich ein Array ausgedacht hat.
*/
typedef struct Sphinx_ Sphinx;

/*
Gibt den Wert an Stelle `i` im Array der Sphinx zurück.
Rufen Sie diese Funktion zu häufig auf, dann schlägt der Test fehl.
*/
uint16_t sphinx_ask(Sphinx *s, size_t i);

#endif