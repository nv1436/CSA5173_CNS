#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5


void createMatrix(char *key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int used[26] = {0}; 
    int keyLength = strlen(key);
    int idx = 0;
    int i;
    char ch;

  
    for ( i = 0; i < keyLength; i++) {
         ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; 
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[idx / MATRIX_SIZE][idx % MATRIX_SIZE] = ch;
            used[ch - 'A'] = 1;
            idx++;
        }
    }

    
    for ( ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!used[ch - 'A']) {
            matrix[idx / MATRIX_SIZE][idx % MATRIX_SIZE] = ch;
            idx++;
        }
    }
}


void findPosition(char letter, char matrix[MATRIX_SIZE][MATRIX_SIZE], int *row, int *col) {
	int i,j;
	char ch;
    for ( i = 0; i < MATRIX_SIZE; i++) {
        for ( j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void decryptDigraph(char a, char b, char matrix[MATRIX_SIZE][MATRIX_SIZE], char *dec1, char *dec2) {
    int row1, col1, row2, col2;
    findPosition(a, matrix, &row1, &col1);
    findPosition(b, matrix, &row2, &col2);

    if (row1 == row2) {  
        *dec1 = matrix[row1][(col1 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
        *dec2 = matrix[row2][(col2 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
    } else if (col1 == col2) {  
        *dec1 = matrix[(row1 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col1];
        *dec2 = matrix[(row2 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col2];
    } else {  
        *dec1 = matrix[row1][col2];
        *dec2 = matrix[row2][col1];
    }
}


void cleanText(char *input, char *output) {
    int idx = 0;
    int i;
    for ( i = 0; i < strlen(input); i++) {
        if (isalpha(input[i])) {
            output[idx++] = toupper(input[i]);
        }
    }
    output[idx] = '\0';
}


int main() {
	int i,j;
    char key[] = "PT109";  
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char cleanedText[1000], decryptedText[1000];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

  
    cleanText(ciphertext, cleanedText);

    
    createMatrix(key, matrix);

    printf("Playfair Cipher Matrix:\n");
    for ( i = 0; i < MATRIX_SIZE; i++) {
        for ( j = 0; j < MATRIX_SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    
    int len = strlen(cleanedText);
    j = 0;
    for ( i = 0; i < len; i += 2) {
        char digraph1 = cleanedText[i];
        char digraph2 = (i + 1 < len) ? cleanedText[i + 1] : 'X';  

        
        char dec1, dec2;
        decryptDigraph(digraph1, digraph2, matrix, &dec1, &dec2);
        decryptedText[j++] = dec1;
        decryptedText[j++] = dec2;
    }
    decryptedText[j] = '\0';  

 
    printf("Decrypted Message: %s\n", decryptedText);

    return 0;
}

