#include <iostream>
#include <vector>
#include <iomanip>
#include "base58.h"
#include "utilities.h"

int main()
{
	std::cout << "Enter a hexstring: ";
	std::string hexstring;
	std::cin >> hexstring;
	std::vector<unsigned char> hexBytes;
	utilities::hexstringToBytes(hexstring, hexBytes);
	std::string b58 = EncodeBase58(hexBytes);
	std::cout << b58 << '\n';

	return 0;
}
