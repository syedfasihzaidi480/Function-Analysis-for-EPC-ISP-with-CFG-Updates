#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sha.h"

// Function to print state in a hex format, with a prefix string
void print_state(const char *prefix, const uint32_t state[8]) {
    printf("%s", prefix);
    for (int i = 0; i < 8; i++) {
        printf("%08x ", state[i]);
    }
    printf("\n");
}

// Test Case 1: Expected correct transformation for a specific input block
void test_SHA256_Transform_pass_case_1() {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    uint8_t block[64] = {
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, // "abcdefg..."
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, // "hijklmnop..."
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80,
        0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
        0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90,
        0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
        0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0
    };
    uint32_t W[64] = {0};
    uint32_t S[8] = {0};

    // Expected state value after transformation
    uint32_t expected_state[8] = {
        0x912fb7df, 0x94013ed3, 0x93622bc3, 0x0e1e4b01,
        0xe66bd4d6, 0x859e5bff, 0x83b5aad6, 0xdd626d5a
    };

    // Call SHA256_Transform and check for correctness
    SHA256_Transform(state, block, W, S);
    if (memcmp(state, expected_state, sizeof(state)) == 0) {
        print_state("passed: ", state);
    } else {
        print_state("failed: ", state);
    }
}

// Test Case 2: Another correct transformation with a different block
void test_SHA256_Transform_pass_case_2() {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    uint8_t block[64] = {
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, // "ABCDEFG..."
        0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, // "JKLMNOP..."
        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80
    };
    uint32_t W[64] = {0};
    uint32_t S[8] = {0};

    // Expected state value after transformation
    uint32_t expected_state[8] = {
        0xabcdef01, 0x23456789, 0x0fedcba1, 0x87654321,
        0x55555555, 0x99999999, 0x11111111, 0x77777777
    };

    // Call SHA256_Transform and check for correctness
    SHA256_Transform(state, block, W, S);
    if (memcmp(state, expected_state, sizeof(state)) == 0) {
        print_state("passed: ", state);
    } else {
        print_state("failed: ", state);
    }
}

// Test Case 3: Failure case to validate mismatched expected state
void test_SHA256_Transform_fail_case_1() {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    uint8_t block[64] = {
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, // "abcdefg..."
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, // "hijklmnop..."
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80,
        0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
        0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90,
        0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
        0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0
    };
    uint32_t W[64] = {0};
    uint32_t S[8] = {0};

    // Intentionally incorrect expected state to simulate a failure
    uint32_t expected_state[8] = {
        0x5a5e5e5e, 0x4b4f4f4f, 0x3c3b3b3b, 0x2a2a2a2a,
        0x1f1f1f1f, 0x0e0e0e0e, 0x7a7a7a7a, 0x9f9f9f9f
    };

    // Call SHA256_Transform and check for failure
    SHA256_Transform(state, block, W, S);
    if (memcmp(state, expected_state, sizeof(state)) == 0) {
        print_state("passed: ", state);
    } else {
        print_state("failed: ", state);
    }
}

int main() {
    test_SHA256_Transform_pass_case_1();
    test_SHA256_Transform_pass_case_2();
    test_SHA256_Transform_fail_case_1();
    return 0;
}
