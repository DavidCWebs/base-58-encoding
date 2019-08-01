#ifndef BASE58_H
#define BASE58_H

#include <stdio.h>
#include <stdlib.h>

size_t base58Encode(const unsigned char *bytes, size_t nBytes, char **b58);

#endif
