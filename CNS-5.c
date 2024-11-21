#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
int main() {
    char plain[100], cipher[100];
    int a, b,i;
    printf("Enter the plaintext: ");
    fgets(plain, sizeof(plain), stdin);
    plain[strcspn(plain, "\n")] = 0;
    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    if (a < 1 || a >= ALPHABET_SIZE) {
        printf("Error: The value of a must be in the range [1, 25].\n");
        return 1;
    }
    int gcd = 1;
    for ( i = 1; i <= a && i <= ALPHABET_SIZE; i++) {
        if (a % i == 0 && ALPHABET_SIZE % i == 0) {
            gcd = i;
        }
    }
    if (gcd != 1) {
        printf("Error: The value of a must be coprime with 26.\n");
        return 1;
    }
    for ( i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            int p = ch - offset;
            int C = (a * p + b) % ALPHABET_SIZE;
            cipher[i] = C + offset;
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
    printf("Ciphertext: %s\n", cipher);
    return 0;
}
