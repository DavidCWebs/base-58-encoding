#include <stdio.h>
#include "getinput.h"
#include "utilities.h"
#include "base58.h"

int main()
{
	char *hexstring = NULL;
	getDynamicInput(&hexstring);

	unsigned char *bytes = NULL;
	size_t nBytes = 0;
	nBytes = hexstringToBytes(hexstring, &bytes);
	for (size_t i = 0; i < nBytes; ++i) {
		printf("%d ", bytes[i]);
	}
	printf("\n");
	
	char *base58 = NULL;
	size_t nb58 = base58Encode(bytes, nBytes, &base58);
	printf("size: %lu %s\n", nb58, base58);
	free(hexstring);
	free(bytes);
	free(base58);
	return 0;
}
