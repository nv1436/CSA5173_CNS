#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8  
#define MAX_LEN 1024  

void xor_encrypt_decrypt(uint8_t *data, uint8_t *key, size_t len) {
	int i;
    for (i = 0; i < len; i++) {
        data[i] ^= key[i % BLOCK_SIZE];
    }
}

void pad_data(uint8_t *data, size_t *len) {
    size_t padding_len = BLOCK_SIZE - (*len % BLOCK_SIZE);
    if (padding_len == BLOCK_SIZE) {
        padding_len = 0;
    }
    data[*len] = 0x80;
    int i;
    for ( i = *len + 1; i < *len + padding_len; i++) {
        data[i] = 0x00;
    }
    *len += padding_len;
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, size_t len) {
	int i;
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        xor_encrypt_decrypt(plaintext + i, key, BLOCK_SIZE);
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
    }
}

void ecb_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *key, size_t len) {
	int i;
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        xor_encrypt_decrypt(ciphertext + i, key, BLOCK_SIZE);
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, size_t len) {
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    int i,j;
    
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        for ( j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= prev_block[j];
        }
        xor_encrypt_decrypt(plaintext + i, key, BLOCK_SIZE);
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *key, uint8_t *iv, size_t len) {
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    int i,j;
    
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
        xor_encrypt_decrypt(plaintext + i, key, BLOCK_SIZE);
        for ( j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= prev_block[j];
        }
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, size_t len) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    int i;
    
    for ( i = 0; i < len; i++) {
        xor_encrypt_decrypt(feedback, key, BLOCK_SIZE);
        ciphertext[i] = plaintext[i] ^ feedback[0];
        memmove(feedback, feedback + 1, BLOCK_SIZE - 1);
        feedback[BLOCK_SIZE - 1] = ciphertext[i];
    }
}

void cfb_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *key, uint8_t *iv, size_t len) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    int i;
    
    for ( i = 0; i < len; i++) {
        xor_encrypt_decrypt(feedback, key, BLOCK_SIZE);
        plaintext[i] = ciphertext[i] ^ feedback[0];
        memmove(feedback, feedback + 1, BLOCK_SIZE - 1);
        feedback[BLOCK_SIZE - 1] = ciphertext[i];
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0xBB, 0xCC, 0xDF, 0xF1};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    uint8_t plaintext[MAX_LEN] = "This is a test message for block cipher modes!";
    size_t len = strlen((char *)plaintext);
    
    pad_data(plaintext, &len);
    
    uint8_t ciphertext[MAX_LEN];
    uint8_t decrypted[MAX_LEN];
    
    printf("Original Plaintext: %s\n", plaintext);
    
    printf("\n--- ECB Encryption/Decryption ---\n");
    ecb_encrypt(plaintext, ciphertext, key, len);
    ecb_decrypt(ciphertext, decrypted, key, len);
    printf("Decrypted: %s\n", decrypted);
    
    printf("\n--- CBC Encryption/Decryption ---\n");
    cbc_encrypt(plaintext, ciphertext, key, iv, len);
    cbc_decrypt(ciphertext, decrypted, key, iv, len);
    printf("Decrypted: %s\n", decrypted);
    
    printf("\n--- CFB Encryption/Decryption ---\n");
    cfb_encrypt(plaintext, ciphertext, key, iv, len);
    cfb_decrypt(ciphertext, decrypted, key, iv, len);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}

