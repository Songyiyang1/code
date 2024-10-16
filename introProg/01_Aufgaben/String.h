#ifndef STRING_H
#define STRING_H

#define START_CAP 8

#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/* A length-delimited, growable byte string. Also keeps a null byte at the end for compatibility with the standard library. */
typedef struct String_ {
    char *buf;
    size_t len;
    size_t cap;
} String;

String str_new() {
    String s;
    s.buf = (char *) malloc(START_CAP);
    s.len = 0;
    s.cap = START_CAP;
    s.buf[0] = 0;

    return s;
}

void str_free(String s) {
    free(s.buf);
}

void str_concat(String *s, const char *s2, size_t s2_len /* excluding any terminating 0 byte */) {
    while (s->len + s2_len >= s->cap) {
        s->cap *= 2;
        s->buf = (char *) realloc(s->buf, s->cap);
    }

    memcpy(s->buf + s->len, s2, s2_len);
    s->len += s2_len;
    s->buf[s->len] = 0;
}

/* Concat a null-terminated string */
void str_str(String *s, const char *s2) {
    str_concat(s, s2, strlen(s2));
}

/* Concat an unsigned number of 64 bit or less */
void str_uint(String *s, uint64_t n) {
    int size = snprintf(NULL, 0, "%" PRIu64, n);
    char* s2 = (char*) malloc(size + 1);
    snprintf(s2, size + 1, "%" PRIu64, n);
    str_concat(s, s2, size);
    free(s2);
}

/* Concat a signed number of 64 bit or less */
void str_int(String *s, int64_t n) {
    int size = snprintf(NULL, 0, "%" PRId64, n);
    char* s2 = (char*) malloc(size + 1);
    snprintf(s2, size + 1, "%" PRId64, n);
    str_concat(s, s2, size);
    free(s2);
}

/* Render an array of u8 and concat it */
void str_u8s(String *s, uint8_t* arr, size_t arr_len) {
    const char *s2 = format_uint8_array(arr, arr_len);
    str_str(s, s2);
    free((char *) s2);
}

/* Render an array of u16 and concat it */
void str_u16s(String *s, uint16_t* arr, size_t arr_len) {
    const char *s2 = format_uint16_array(arr, arr_len);
    str_str(s, s2);
    free((char *) s2);
}

#endif