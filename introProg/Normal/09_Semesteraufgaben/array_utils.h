#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdint.h>

#include "array.h"
#include "String.h"

void render_array(String *s, Array arr) {
    str_u16s(s, arr.arr, arr.len);
}

Array copy_array(Array arr) {
    Array ret;
    ret.arr = copy_u16s(arr.arr, arr.len);
    ret.len = arr.len;
    return ret;
}

#endif