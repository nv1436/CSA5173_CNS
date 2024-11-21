#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


void generateCipherAlphabet(const char* keyword, char* cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0}; // Array to track used letters
    int idx = 0;
    int i;
    char ch;

   
    for ( i = 0; i < strlen(keyword); i++) {
        char ch = toupper(keyword[i]);
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            cipherAlphabet[idx++] = ch;
            used[ch - 'A'] = 1;  
        }
    }

  
    for ( ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[idx++] = ch;
        }
    }
}


void encrypt(const char* plain, const char* cipherAlphabet, char* cipher) {
	int i;
	char ch;
    for ( i = 0; i < strlen(plain); i++) {
         ch = toupper(plain[i]);
        if (ch >= 'A' && ch <= 'Z') {
           
            int index = ch - 'A';
            cipher[i] = cipherAlphabet[index];
        } else {
            
            cipher[i] = plain[i];
        }
    }
    cipher[strlen(plain)] = '\0';  
}


void decrypt(const char* cipher, const char* cipherAlphabet, char* plain) {
	int i;
	char ch;
    for ( i = 0; i < strlen(cipher); i++) {
         ch = toupper(cipher[i]);
        if (ch >= 'A' && ch <= 'Z') {
            
            int index = strchr(cipherAlphabet, ch) - cipherAlphabet;
            plain[i] = 'A' + index;
        } else {
            
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';  
}

int main() {
    char keyword[] = "CIPHER";
    char plain[1000], cipher[1000], decryptedText[1000];

    char cipherAlphabet[ALPHABET_SIZE + 1]; 
    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Cipher Alphabet: %s\n", cipherAlphabet);

    printf("Enter plaintext message: ");
    fgets(plain, sizeof(plain), stdin);

  
    encrypt(plain, cipherAlphabet, cipher);
    printf("Encrypted ciphertext: %s\n", cipher);

    decrypt(cipher, cipherAlphabet, decryptedText);
    printf("Decrypted plaintext: %s\n", decryptedText);

    return 0;
}

