#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>

/* Ein uint16_t Array zusammen mit seiner Länge. */
typedef struct Array_ {
    uint16_t *arr;
    size_t len;
} Array;

#endif