#!/usr/bin/env python3

from binascii import unhexlify

b58_chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"

def base58(bytes):
    i = 8 * (len(bytes) - 1)
    result = 0
    for b in bytes:
        result |= b << i
        i -= 8
    
    b58 = ""
    while result:
        b58 = b58_chars[result % 58] + b58
        result = result // 58

    return b58

def string_to_base58(preimage):
    return base58(preimage.encode('utf-8'))

def hexstring_to_base58(hexstring):
    return base58(unhexlify(hexstring))

def main():
    preimage = input("Enter a string: ")
    if all(c in 'abcdefABCDEF0123456789' for c in preimage) and len(preimage) % 2 == 0:
        print(hexstring_to_base58(preimage))
    else:
        print(string_to_base58(preimage))

if __name__ == '__main__':
    main()

# # prefix byte set as last step of key hashing to address process.
#6fabccfd87163dbcfba881aae7020cdcb6dcc10c2dcbda1542
