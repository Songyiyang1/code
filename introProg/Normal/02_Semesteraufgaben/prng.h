#ifndef PRNG_H
#define PRNG_H

#include <stdint.h>

uint64_t seed = 42;

uint64_t randu64() {
  seed ^= (seed << 13);
  seed ^= (seed >> 7);
  seed ^= (seed << 17);
  return seed;
}

void randomly_permute_u8s(uint8_t *arr, size_t len) {
  for (size_t count = 0; count < 8 * len; count++) {
    size_t i = randu64() % len;
    size_t j = randu64() % len;
    uint8_t tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

#endif