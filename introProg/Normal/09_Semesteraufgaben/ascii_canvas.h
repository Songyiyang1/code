#ifndef ASCII_CANVAS_H
#define ASCII_CANVAS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AsciiCanvas_ {
    uint16_t width;
    uint16_t height;
    char *buffer;
} AsciiCanvas;

AsciiCanvas ascii_new(uint16_t width, uint16_t height) {
    size_t len = height * (width + 1);
    char *buffer = malloc(len + 1);
    buffer[len] = 0;

    for (size_t i = 0; i < len; i++) {
        buffer[i] = ' ';
    }

    for (size_t i = 1; i <= height; i++) {
        buffer[i * (width + 1) - 1] = '\n';
    }

    AsciiCanvas ac = {
        .width = width,
        .height = height,
        .buffer = buffer,
    };
    return ac;
}

void ascii_free(AsciiCanvas ac) {
    free(ac.buffer);
}

void ascii_set(AsciiCanvas *ac, char c, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1) || y >= ac->height) {
        fprintf(stderr, "invalid AsciiCanvas set at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    ac->buffer[y * (ac->width + 1) + x] = c;
}

char ascii_get(AsciiCanvas *ac, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1) || y >= ac->height) {
        fprintf(stderr, "invalid AsciiCanvas get at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    return ac->buffer[y * (ac->width + 1) + x];
}

char *ascii_get_str(AsciiCanvas *ac, uint16_t x, uint16_t y) {
    if (x < 0 || y < 0 || x > (ac->width + 1)|| y >= ac->height) {
        fprintf(stderr, "invalid AsciiCanvas get_str at x = %d, y = %d on a %d x %d canvas\n", x, y, ac->width, ac->height);
        abort();
    }

    return ac->buffer + (y * (ac->width + 1) + x);
}

#endif