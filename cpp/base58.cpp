// Copyright (c) 2014-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
// See https://stackoverflow.com/a/2424309/3590673

#include "base58.h"

static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"; 

std::string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend)
{
	// Skip & count leading zeroes.
	int zeroes = 0;
	int length = 0;
	while (pbegin != pend && *pbegin == 0) {
		pbegin++;
		zeroes++;
	}
	// Allocate enough space in big-endian base58 representation.
	int size = (pend - pbegin) * 138 / 100 + 1; // log(256) / log(58), rounded up.
	std::vector<unsigned char> b58(size);

	std::cout << "-------" << '\n';
	// Process the bytes.
	while (pbegin != pend) {
		// carry is the current byte value as an int
		int carry = *pbegin;
		int i = 0;
		std::cout << "while loop carry: " << carry << '\n';
		
		// Step through results vector
		// Apply "b58 = b58 * 256 + ch". 
		//
		// (A * B) % MOD = ((A % MOD) * (B % MOD)) % MOD
		// (A + B) % MOD = ((A % MOD) + (B % MOD)) % MOD
		//
		// In the specific case of mod 58:
		// (A * B) % 58 = ((A % 58) * (B % 58)) % 58
		//
		//
		// Stop if carry == 0 or if i is less than length
		//
		// -------------------
		std::vector<unsigned char>::reverse_iterator it;
		for (it = b58.rbegin(); (carry != 0 || i < length) && (it != b58.rend()); it++, i++) {
			// ----------------------------------------------------------------------------------
			// Convert the base of the current byte and also add any values
			// calculated for previous byte-conversions.
			//
			// If `*it` contains a value, it means that a more significant byte was
			// stored already. The actual value that needs to be added at this 
			// position is therefore `256 * (*it)`, because the value is from a 
			// byte one higher. Bytes are basically a collection of digits
			// representing a base 256 number. For example, 3 bytes represents:
			//
			// x = (a*256^2) + (b*(256^1)) + (c*(256^0))
			//
			// Once the addition has been carried out, the modulus base 58
			// of this number is stored at the current position,
			// with the result of integer division carried forward into
			// the next iteration of the for-loop and the reverse-next 
			// position of the results vector.
			//
			// This continues until the carry value is zero - at which point the 
			// base conversion is complete.
			//
			// This method means that enormous numbers do not need to be handled.
			// At each level of byte-processing, the largest number that will be used
			// in computation is:
			//
			// (57 * 256) + 57 = 14649
			//
			// This is well within normal space bounds for C & C++.
			// ----------------------------------------------------------------------------------
			carry += 256 * (*it);
			*it = carry % 58;
			carry /= 58;
		}

		assert(carry == 0);
		length = i;
		pbegin++;
		std::cout << "-------" << '\n';
	}
	// Skip leading zeroes in base58 result.
	std::vector<unsigned char>::iterator it = b58.begin() + (size - length);
	while (it != b58.end() && *it == 0)
		it++;
	// Translate the result into a string.
	std::string str;
	str.reserve(zeroes + (b58.end() - it));
	str.assign(zeroes, '1');
	while (it != b58.end())
		str += pszBase58[*(it++)];
	return str;
}

std::string EncodeBase58(const std::vector<unsigned char>& vch)
{
	return EncodeBase58(vch.data(), vch.data() + vch.size());
}

