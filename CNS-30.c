#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 8

void block_cipher(unsigned char *block, unsigned char *key) {
	int i;
    for ( i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void cbc_mac(unsigned char *key, unsigned char *message, size_t message_len, unsigned char *mac) {
    unsigned char iv[BLOCK_SIZE] = {0};
    unsigned char previous_block[BLOCK_SIZE] = {0};
    int i,j;

    for ( i = 0; i < message_len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        size_t block_len = (i + BLOCK_SIZE <= message_len) ? BLOCK_SIZE : message_len - i;

        memset(block, 0, BLOCK_SIZE);
        memcpy(block, message + i, block_len);

        for ( j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= previous_block[j] ^ iv[j];
        }

        block_cipher(block, key);

        memcpy(previous_block, block, BLOCK_SIZE);
    }

    memcpy(mac, previous_block, BLOCK_SIZE);
}

void print_hex(unsigned char *data, size_t len) {
	int i;
    for ( i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    unsigned char message_x[BLOCK_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    unsigned char mac[BLOCK_SIZE];
    cbc_mac(key, message_x, BLOCK_SIZE, mac);

    printf("MAC(T) for message X: ");
    print_hex(mac, BLOCK_SIZE);

    unsigned char message_two_blocks[2 * BLOCK_SIZE];
    memcpy(message_two_blocks, message_x, BLOCK_SIZE);
    int i;

    for ( i = 0; i < BLOCK_SIZE; i++) {
        message_two_blocks[BLOCK_SIZE + i] = message_x[i] ^ mac[i];
    }

    unsigned char mac_two_blocks[BLOCK_SIZE];
    cbc_mac(key, message_two_blocks, 2 * BLOCK_SIZE, mac_two_blocks);

    printf("MAC for two-block message X || (X ? T): ");
    print_hex(mac_two_blocks, BLOCK_SIZE);

    if (memcmp(mac, mac_two_blocks, BLOCK_SIZE) == 0) {
        printf("The MACs are the same! The adversary can forge the MAC for the two-block message.\n");
    } else {
        printf("The MACs are different.\n");
    }

    return 0;
}

