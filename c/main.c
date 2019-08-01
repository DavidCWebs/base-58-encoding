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
	char *base58 = NULL;

	// If the size of encoded bytes is needed:
	// size_t sizeBase58 = base58Encode(bytes, nBytes, &base58);
	
	base58Encode(bytes, nBytes, &base58);
	printf("Base58:\n%s\n", base58);
	free(hexstring);
	free(bytes);
	free(base58);
	return 0;
}
