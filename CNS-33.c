#include <stdio.h>
#include <string.h>
#include <stdint.h>

static const int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
                         60, 52, 44, 36, 28, 20, 12, 4,
                         62, 54, 46, 38, 30, 22, 14, 6,
                         64, 56, 48, 40, 32, 24, 16, 8,
                         57, 49, 41, 33, 25, 17, 9, 1,
                         59, 51, 43, 35, 27, 19, 11, 3,
                         61, 53, 45, 37, 29, 21, 13, 5,
                         63, 55, 47, 39, 31, 23, 15, 7};

static const int FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
                         39, 7, 47, 15, 55, 23, 63, 31,
                         38, 6, 46, 14, 54, 22, 62, 30,
                         37, 5, 45, 13, 53, 21, 61, 29,
                         36, 4, 44, 12, 52, 20, 60, 28,
                         35, 3, 43, 11, 51, 19, 59, 27,
                         34, 2, 42, 10, 50, 18, 58, 26,
                         33, 1, 41, 9, 49, 17, 57, 25};

void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
}

uint32_t des_round(uint32_t right, uint64_t subkey) {
    return right ^ subkey;
}

uint64_t apply_initial_permutation(uint64_t data) {
    uint64_t result = 0;
    int i;
    for ( i = 0; i < 64; i++) {
        result |= ((data >> (64 - IP[i])) & 1) << (63 - i);
    }
    return result;
}

uint64_t apply_final_permutation(uint64_t data) {
    uint64_t result = 0;
    int i;
    for ( i = 0; i < 64; i++) {
        result |= ((data >> (64 - FP[i])) & 1) << (63 - i);
    }
    return result;
}

uint64_t des_encrypt(uint64_t data, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);
    uint64_t permuted_data = apply_initial_permutation(data);
    uint32_t left = (permuted_data >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_data & 0xFFFFFFFF;
    int round;
    for ( round = 0; round < 16; round++) {
        uint32_t new_right = des_round(right, subkeys[round]);
        uint32_t new_left = left ^ new_right;
        left = new_left;
        right = right;
    }
    uint64_t combined = ((uint64_t)left << 32) | right;
    return apply_final_permutation(combined);
}

uint64_t des_decrypt(uint64_t data, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);
    uint64_t permuted_data = apply_initial_permutation(data);
    uint32_t left = (permuted_data >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_data & 0xFFFFFFFF;
    int round;
    for ( round = 15; round >= 0; round--) {
        uint32_t new_right = des_round(right, subkeys[round]);
        uint32_t new_left = left ^ new_right;
        left = new_left;
        right = right;
    }
    uint64_t combined = ((uint64_t)left << 32) | right;
    return apply_final_permutation(combined);
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t data = 0x0123456789ABCDEF;
    uint64_t encrypted_data = des_encrypt(data, key);
    printf("Encrypted Data: %016llx\n", encrypted_data);
    uint64_t decrypted_data = des_decrypt(encrypted_data, key);
    printf("Decrypted Data: %016llx\n", decrypted_data);
    return 0;
}

