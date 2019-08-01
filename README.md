Base58: Bitcoin Legacy Address Encoding
========================================

Base58 is a binary to text encoding scheme that Satoshi Nakamoto introduced in the earliest incarnation of Bitcoin.

Base58 allows a large number to be represented in a compact and human-readable way such that transcription errors are minimised.

The Base58 "alphabet" does not include: '0', 'O', 'I' or 'l' because these characters may be confused in certain fonts.

> Why base-58 instead of standard base-64 encoding?
> - Don't want 0OIl characters that look the same in some fonts and could be used to create visually identical looking account numbers.
> - A string with non-alphanumeric characters is not as easily accepted as an account number.
> - E-mail usually won't line-break if there's no punctuation to break at.
> - Doubleclicking selects the whole number as one word if it's all alphanumeric.
> 
> --Comment by Satoshi Nakamoto, 2009 Bitcoin v0.01 ALPHA codebase: `src/base58.h`

Base 64 is mentioned - this encoding scheme is typically used when binary data needs to be represented in ASCII string format.

Why is Encoding Necessary?
--------------------------
A collection of Bytes is a set of numbers between 0 and 255. 255 is the maximum number that can be represented by an 8-bit byte, or 2⁸ - 1, and zero is obviously the lowest representable number. Bytes are important because they are generally the smallest addressable unit of memory in most modern computer architectures.

If you want to print this collection, or send electronically in human-readable format, you have a problem because some of these numbers do not map to printable ASCII characters.

You could represent each byte in binary, with each eight bits representing a byte - but for anything more than a few bytes, this would be impractical.

Another option is to represent each byte as hexadecimal symbols. In this case, if you have `n` bytes, a maximum of `2n` characters are required to represent the bytes. For practical purposes, some kind of zero padding is also necessary, so that you can distinguish byte boundaries for decoding purposes i.e. if a byte has the value `A` it would become `0A`.

Consider printing the collection of bytes : `[222, 173, 190, 239]`.

Although you could print these bytes using binary digits, even with just four bytes it looks impractical:

```
         +----------+----------+----------+----------+
Decimal: | 222      | 173      | 190      | 239      |
         |          |          |          |          |
Binary:  | 11011110 | 10101101 | 10111110 | 11101111 |
         +----------+----------+----------+----------+
```
...so if you want to print these bytes in human-readable(!) format: `11011110101011011011111011101111`. This is not human-readable - try reading that out over the phone.

The situation is a bit better with hexadecimal:

```
         +----------+----------+----------+----------+
Decimal: | 222      | 173      | 190      | 239      |
         |          |          |          |          |
Hex:     | DE       | AD       | BE       | EF       |
         +----------+----------+----------+----------+
```

This is a lot better - but if you wanted to share a Bitcoin public key (e.g. to receive payment) the raw bytes look like this:

```
[2,80,134,58,214,74,135,174,138,47,232,60,26,241,168,64,60,181,63,83,228,134,216,81,29,173,138,4,136,126,91,35,82]
```
...and the hex string looks like this:


```
0250863ad64a87ae8a2fe83c1af1a8403cb53f53e486d8511dad8a04887e5b2352
```

The same address encoded in Base58Check encoding is:

```
1PMycacnJaSqwwJqjawXBErnLsZ7RkXUAs
```

It's still pretty long, but much more manageable. There's no chance of mixing up the character '1' with the character 'l' because the encoding does not contain the 'l' character (or '0', 'O' and 'I').


Encoding Bitcoin Public Keys
----------------------------
In the context of Bitcoin, we need to represent ECDSA public keys in a way that is human readable and which minimises transcription errors. Such are typically 33 bytes in length - requiring 66 hexadecimal digits or 264 binary digits.


Radix 64
--------
Encoding a message (such as a bitcoin public key) as Radix 64 allows the message to be printed and/or sent as an email or text message - modes of communication which do not allow the transfer of binary data.

The above key would be represented as:

```
AlCGOtZKh66KL+g8GvGoQDy1P1PkhthRHa2KBIh+WyNS
```


Byte Collection as Radix 256 Digits
-----------------------------------

```
d1bn−1 + d2bn−2 + … + dnb0, where 0 ≤ di < b
```

TO BE COMPLETED.

References
----------
* [Bitcoin Base58Check Encoding][1]
* [Technical background, version 1 Bitcoin Addresses][2]

[1]: https://en.bitcoin.it/Base58Check_encoding
[2]: https://en.bitcoin.it/wiki/Technical_background_of_version_1_Bitcoin_addresses
