#include <stdio.h>

typedef unsigned char byte;

void print_hex(byte *data, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void generate_subkeys(byte *initial_key, int block_size, byte *const_Rb, byte *subkey1, byte *subkey2) {
    byte L[block_size / 8];
    int i;
    byte msb = (initial_key[0] & 0x80) ? 0x87 : 0x00;
    for (i = 0; i < block_size / 8; i++) {
        L[i] = (initial_key[i] << 1) | ((i < block_size / 8 - 1) ? (initial_key[i + 1] >> 7) : 0);
    }
    for (i = 0; i < block_size / 8; i++) {
        subkey1[i] = L[i] ^ const_Rb[i];
    }
    byte carry = (L[0] & 0x80) ? 1 : 0;
    for (i = 0; i < block_size / 8; i++) {
        L[i] = (L[i] << 1) | carry;
        carry = (L[i] & 0x80) ? 1 : 0;
    }
    for (i = 0; i < block_size / 8; i++) {
        subkey2[i] = L[i] ^ const_Rb[i];
    }
}

int main() {
    int block_size = 128;
    int i;
    byte initial_key[block_size / 8];
    byte subkey1[block_size / 8];
    byte subkey2[block_size / 8];
    byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x8a, 0xed, 0x2a, 0x6a, 
                    0xbf, 0x71, 0x58, 0x80, 0x9c, 0xf4, 0xf3, 0xc0};

    for (i = 0; i < block_size / 8; i++) {
        initial_key[i] = key[i];
    }

    byte const_Rb[block_size / 8];
    if (block_size == 64) {
        byte const_64 = 0x1B;
        for (i = 0; i < block_size / 8; i++) {
            const_Rb[i] = const_64;
        }
    } else if (block_size == 128) {
        byte const_128 = 0x87;
        for (i = 0; i < block_size / 8; i++) {
            const_Rb[i] = const_128;
        }
    } else {
        printf("Unsupported block size\n");
        return 1;
    }

    generate_subkeys(initial_key, block_size, const_Rb, subkey1, subkey2);

    printf("Subkey 1: ");
    print_hex(subkey1, block_size / 8);

    printf("Subkey 2: ");
    print_hex(subkey2, block_size / 8);

    return 0;
}

