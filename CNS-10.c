#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5


void createMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int i,j;
  
    char playfair_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    
    for ( i = 0; i < MATRIX_SIZE; i++) {
        for ( j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = playfair_matrix[i][j];
        }
    }
}


void findPosition(char letter, char matrix[MATRIX_SIZE][MATRIX_SIZE], int *row, int *col) {
	int i,j;
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


void encryptDigraph(char a, char b, char matrix[MATRIX_SIZE][MATRIX_SIZE], char *enc1, char *enc2) {
    int row1, col1, row2, col2;
    findPosition(a, matrix, &row1, &col1);
    findPosition(b, matrix, &row2, &col2);

    if (row1 == row2) {  
        *enc1 = matrix[row1][(col1 + 1) % MATRIX_SIZE];
        *enc2 = matrix[row2][(col2 + 1) % MATRIX_SIZE];
    } else if (col1 == col2) {  
        *enc1 = matrix[(row1 + 1) % MATRIX_SIZE][col1];
        *enc2 = matrix[(row2 + 1) % MATRIX_SIZE][col2];
    } else {  
        *enc1 = matrix[row1][col2];
        *enc2 = matrix[row2][col1];
    }
}


void preprocessText(char *input, char *output) {
    int idx = 0;
    int len = strlen(input);
    int i;
    for ( i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            output[idx++] = toupper(input[i]);
        }
    }

  
    if (idx % 2 != 0) {
        output[idx++] = 'X';  
    }
    output[idx] = '\0';
}


void encryptPlayfair(char *plaintext, char *ciphertext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    char preprocessedText[1000];
    preprocessText(plaintext, preprocessedText);

    int len = strlen(preprocessedText);
    int idx = 0;
    int i;

 
    for ( i = 0; i < len; i += 2) {
        char digraph1 = preprocessedText[i];
        char digraph2 = preprocessedText[i + 1];

        
        char enc1, enc2;
        encryptDigraph(digraph1, digraph2, matrix, &enc1, &enc2);
        ciphertext[idx++] = enc1;
        ciphertext[idx++] = enc2;
    }
    ciphertext[idx] = '\0';  
}

int main() {
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

   
    createMatrix(matrix);
    int i,j;


    printf("Playfair Cipher Matrix:\n");
    for ( i = 0; i < MATRIX_SIZE; i++) {
        for ( j = 0; j < MATRIX_SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

  
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[1000];

    
    encryptPlayfair(plaintext, ciphertext, matrix);

    
    printf("Encrypted ciphertext: ");
    for (i = 0; i < strlen(ciphertext); i++) {
        printf("%c", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

