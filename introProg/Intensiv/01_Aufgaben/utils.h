#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
Utility functions used throughout the codebase.
*/

/*
Try to malloc, abort when out of memory.
*/
void* mallocx(size_t size) {
    void * allocation = malloc(size);

    if (allocation) {
        return allocation;
    } else {
        printf("Out of memory");
        abort();
    }
}

uint8_t *copy_u8s(uint8_t *arr, size_t len) {
    uint8_t *r = (uint8_t *) malloc(len);
    memcpy(r, arr, len);
    return r;
}

uint16_t *copy_u16s(uint16_t *arr, size_t len) {
    uint16_t *r = (uint16_t *) malloc(sizeof(uint16_t) * len);
    memcpy(r, arr, sizeof(uint16_t) * len);
    return r;
}

const char *format_uint8_array(uint8_t* arr, size_t arr_len) {
    if (arr_len == 0) {
        char *str = mallocx(3);
        str[0] = '[';
        str[1] = ']';
        str[2] = 0;
        return str;
    }

    size_t sum_of_digits = 0;
    for(int i = 0; i < arr_len; i++){
        size_t size = snprintf(NULL, 0, "%d", arr[i]);
        sum_of_digits += size;
    }

    size_t string_len = sum_of_digits + (arr_len-1)*2 /*number of commas*/ + 2 /*brackets*/ + 1;
    char* array_string = mallocx(string_len);
    char *ptr = array_string;

    *ptr = '[';
    ptr += 1;

    for (size_t i = 0; i < arr_len; i++) { 
        ptr += sprintf(ptr, "%d", arr[i]);
        if (i < arr_len - 1) {
            ptr += sprintf(ptr, ", ");
        }
    }

    *ptr = ']';
    ptr += 1;
    *ptr = 0;

    return array_string;
}

const char *format_uint16_array(uint16_t* arr, size_t arr_len) {
    if (arr_len == 0) {
        char *str = mallocx(3);
        str[0] = '[';
        str[1] = ']';
        str[2] = 0;
        return str;
    }

    size_t sum_of_digits = 0;
    for(int i = 0; i < arr_len; i++){
        size_t size = snprintf(NULL, 0, "%d", arr[i]);
        sum_of_digits += size;
    }

    size_t string_len = sum_of_digits + (arr_len-1)*2 /*number of commas*/ + 2 /*brackets*/ + 1;
    char* array_string = mallocx(string_len);
    char *ptr = array_string;

    *ptr = '[';
    ptr += 1;

    for (size_t i = 0; i < arr_len; i++) { 
        ptr += sprintf(ptr, "%d", arr[i]);
        if (i < arr_len - 1) {
            ptr += sprintf(ptr, ", ");
        }
    }

    *ptr = ']';
    ptr += 1;
    *ptr = 0;

    return array_string;
}

/*
Return whether the given string contains characters which might make trouble in a file name.
*/
bool is_invalid_filename(char* name) {
    int len = strlen(name);

    for(int i = 0; i<len;i++){
        if(name[i] == '/' || name[i] == '\\' || name[i] == '<' || name[i] == '>' || name[i] == '|'
            || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '"'){
            return true;
        }
    }

    return false;
}

/*
Number of characters you need to render a `uint16_t` in base 10.
*/
size_t ascii_width_u16(uint16_t n) {
    return n == 0 ? 1 : floor(log10(n)) + 1;
}

/*
Number of characters you need to render a `size_t` in base 10.
*/
size_t ascii_width_size(size_t n) {
    return n == 0 ? 1 : floor(log10(n)) + 1;
}

#endif