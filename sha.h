#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stddef.h>

// Macros for bitwise operations
#define ROTR32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define Ch(x, y, z) ((x & (y ^ z)) ^ z)
#define Maj(x, y, z) ((x & (y | z)) | (y & z))
#define SHR(x, n) ((x) >> (n))
#define ROTR(x, n) ROTR32(x, n)
#define S0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define S1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define s0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define s1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// Function declarations
void SHA256_Transform(uint32_t state[8], const uint8_t block[64], uint32_t W[64], uint32_t S[8]);

#endif // SHA_H
