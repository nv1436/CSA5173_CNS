#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16

void print_hex(unsigned char *data, size_t length) {
	int i;
    for ( i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void pad_data(unsigned char *data, size_t *length) {
	int i;
    size_t padding_length = BLOCK_SIZE - (*length % BLOCK_SIZE);
    for ( i = *length; i < *length + padding_length; i++) {
        data[i] = (unsigned char)padding_length;
    }
    *length += padding_length;
}

void xor_cipher(unsigned char *data, unsigned char *key, size_t length) {
	int i;
    for ( i = 0; i < length; i++) {
        data[i] ^= key[i % BLOCK_SIZE];
    }
}

void ecb_encrypt(unsigned char *data, size_t length, unsigned char *key, unsigned char *ciphertext) {
	int i;
    for ( i = 0; i < length; i += BLOCK_SIZE) {
        xor_cipher(data + i, key, BLOCK_SIZE);
        memcpy(ciphertext + i, data + i, BLOCK_SIZE);
    }
}

void cbc_encrypt(unsigned char *data, size_t length, unsigned char *key, unsigned char *ciphertext, unsigned char *iv) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    int j,i;
    for ( i = 0; i < length; i += BLOCK_SIZE) {
        for ( j = 0; j < BLOCK_SIZE; j++) {
            data[i + j] ^= prev_block[j];
        }
        xor_cipher(data + i, key, BLOCK_SIZE);
        memcpy(ciphertext + i, data + i, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(unsigned char *data, size_t length, unsigned char *key, unsigned char *ciphertext, unsigned char *iv) {
    unsigned char feedback[BLOCK_SIZE];
    unsigned char temp_block[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    int i,j;
    for ( i = 0; i < length; i += BLOCK_SIZE) {
        xor_cipher(feedback, key, BLOCK_SIZE);
        for ( j = 0; j < BLOCK_SIZE && i + j < length; j++) {
            ciphertext[i + j] = data[i + j] ^ feedback[j];
        }
        memcpy(feedback, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char data[] = "This is a secret message. Encryption is fun!";
    size_t data_len = strlen((char *)data);
    pad_data(data, &data_len);
    
    unsigned char key[BLOCK_SIZE] = {0x1b, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
    unsigned char iv[BLOCK_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
    
    unsigned char ciphertext[256];
    
    printf("Original plaintext:\n");
    print_hex(data, data_len);
    
    ecb_encrypt(data, data_len, key, ciphertext);
    printf("Ciphertext (ECB mode):\n");
    print_hex(ciphertext, data_len);
    
    cbc_encrypt(data, data_len, key, ciphertext, iv);
    printf("Ciphertext (CBC mode):\n");
    print_hex(ciphertext, data_len);
    
    cfb_encrypt(data, data_len, key, ciphertext, iv);
    printf("Ciphertext (CFB mode):\n");
    print_hex(ciphertext, data_len);
    
    return 0;
}

