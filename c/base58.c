#include "base58.h"

static char b58Chars[] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J',
	'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c',
	'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z'
};

size_t base58Encode(const unsigned char *bytes, size_t nBytes, char **b58)
{
	size_t zeroes = 0, k = 0;
	while(bytes[k++] == 0) {
		zeroes++;
	}
	printf("zeroes: %lu\n", zeroes);

	size_t b58Size = nBytes * 138 / 100 + 1;
	*b58 = calloc(b58Size, sizeof(*b58) + 1);
	char *digits = calloc(b58Size, sizeof(digits));

	for (size_t i = 0; i < nBytes; ++i) {
		int carry = bytes[i];
		size_t j = b58Size;
		while (carry) {
			carry += 256 * digits[j];
			digits[j] = carry % 58;
			carry /= 58;
			j--;			
		}
	}
	size_t i, j, leadingZeroes = 0;
	//set i to skip leading zeroes.
	for (i = 0; i <= b58Size; i++) {
		if (digits[i] != 0) {
			break;
		} else {
			leadingZeroes++;
		}
	}
	for (j = 0; i <= b58Size; i++, j++) {
		*(*b58 + j) = b58Chars[(int)digits[i]];
	}
	*(*b58 + j + 1) = 0;
	
	free(digits);
	return b58Size;
}

