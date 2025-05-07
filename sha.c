#include "sha.h"
#include <string.h>
#include <stdio.h>

// Big-endian load/store macros
#define LOAD32_BE(p) \
    (((uint32_t)(p)[0] << 24) | ((uint32_t)(p)[1] << 16) | ((uint32_t)(p)[2] << 8) | ((uint32_t)(p)[3]))

#define STORE32_BE(p, v)        \
    do {                        \
        (p)[0] = (v) >> 24;     \
        (p)[1] = (v) >> 16;     \
        (p)[2] = (v) >> 8;      \
        (p)[3] = (v);           \
    } while (0)

// Define RNDr for SHA256 transformation rounds
#define RNDr(S, W, j, i)                                      \
    do {                                                       \
        uint32_t temp1 = S[7] + S1(S[4]) + Ch(S[4], S[5], S[6]) + Krnd[i + j] + W[i + j]; \
        uint32_t temp2 = S0(S[0]) + Maj(S[0], S[1], S[2]);     \
        S[7] = S[6];                                           \
        S[6] = S[5];                                           \
        S[5] = S[4];                                           \
        S[4] = S[3] + temp1;                                   \
        S[3] = S[2];                                           \
        S[2] = S[1];                                           \
        S[1] = S[0];                                           \
        S[0] = temp1 + temp2;                                  \
    } while (0)

// Define MSCH for the message schedule (expansion of the 16-word message block)
#define MSCH(W, j, i)                       \
    do {                                    \
        uint32_t temp = W[i + j] + s1(W[i + j - 2]) + W[i + j - 7] + s0(W[i + j - 15]); \
        W[i + j] = temp;                    \
    } while (0)

static const uint32_t Krnd[64] = {
    // (same Krnd array as before)
};

// Big-endian word decoding
static void be32dec_vect(uint32_t *dst, const unsigned char *src, size_t len) {
    for (size_t i = 0; i < len / 4; i++) {
        dst[i] = LOAD32_BE(src + i * 4);
    }
}

// Main SHA256 Transform function
void SHA256_Transform(uint32_t state[8], const uint8_t block[64], uint32_t W[64], uint32_t S[8]) {
    int i;

    // Load the message block into the message schedule array
    be32dec_vect(W, block, 64);

    // Copy the current state to the working state array S
    memcpy(S, state, 32);

    // Print header for the table
    printf("Round |    S0    |    S1    |    S2    |    S3    |    S4    |    S5    |    S6    |    S7    \n");
    printf("--------------------------------------------------------------\n");

    // Perform the rounds
    for (i = 0; i < 64; i++) {
        if (i < 16) {
            RNDr(S, W, 0, i);
        } else {
            MSCH(W, 1, i);
            RNDr(S, W, 1, i);
        }

        // Print the state after each round in a table format
        printf("%3d   | ", i);
        for (int j = 0; j < 8; j++) {
            printf("%08x | ", S[j]);
        }
        printf("\n");
    }

    // Update the state with the final result
    for (i = 0; i < 8; i++) {
        state[i] += S[i];
    }
}
