#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8    
#define KEY_SIZE 24     


void des_encrypt(uint64_t *block, uint64_t key) {
    
    *block ^= key; 
}


void triple_des_cbc(uint8_t *input, uint8_t *output, uint64_t *key, uint8_t *iv, int length) {
    uint64_t block;
    uint64_t keys[3] = { key[0], key[1], key[2] };
    uint64_t iv_block;
    uint64_t temp;
    int i,j;

    
    iv_block = *((uint64_t*)iv);

    for ( i = 0; i < length; i += BLOCK_SIZE) {
        
        block = 0;
        for ( j = 0; j < BLOCK_SIZE; j++) {
            block = (block << 8) | input[i + j];
        }

       
        block ^= iv_block;

       
        des_encrypt(&block, keys[0]);
        des_encrypt(&block, keys[1]); 
        des_encrypt(&block, keys[2]); 
        int j,i;

        
        for ( j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] = (block >> (8 * (BLOCK_SIZE - 1 - j))) & 0xFF;
        }

        iv_block = block;
    }
}

int main() {
    
    uint64_t key[3] = { 0x0123456789abcdef, 0xabcdef0123456789, 0x1234567890abcdef };
    
    uint8_t iv[BLOCK_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    uint8_t input[] = "12345678";  
    uint8_t output[BLOCK_SIZE];    

    printf("Plaintext: ");
    int i,j;
    for ( i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", input[i]);
    }
    printf("\n");

 
    triple_des_cbc(input, output, key, iv, sizeof(input));

   
    printf("Ciphertext: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}

