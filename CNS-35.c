#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 1000

void generate_key(int *key, int length) {
    srand(time(NULL));
    int i;
    for ( i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}

void otp_vigenere_encrypt(char *plaintext, char *ciphertext, int *key, int length) {
	int i;
    for ( i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

void otp_vigenere_decrypt(char *ciphertext, char *plaintext, int *key, int length) {
	int i;
    for ( i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[MAX_LEN];
    char ciphertext[MAX_LEN];
    char decrypted[MAX_LEN];
    int key[MAX_LEN];
    
    printf("Enter the plaintext (only alphabetic characters): ");
    fgets(plaintext, MAX_LEN, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    
    int length = strlen(plaintext);
    
    generate_key(key, length);
    
    otp_vigenere_encrypt(plaintext, ciphertext, key, length);
    printf("Ciphertext: %s\n", ciphertext);
    
    otp_vigenere_decrypt(ciphertext, decrypted, key, length);
    printf("Decrypted Text: %s\n", decrypted);
    
    return 0;
}

