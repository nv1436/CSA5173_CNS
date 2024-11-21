#include <stdio.h> 
#include <string.h> 
 
char decryptChar(int c, int a, int b) { 
    return ((a * (c - b)) % 26 + 26) % 26 + 'A'; 
} 
 
int main() { 
     int a;
	 int b;
    char cipher[1000]; 
    printf("Enter the ciphertext: "); 
    scanf("%s", cipher); 
 
    int mostFrequent = cipher[0]; 
    int secondMostFrequent = cipher[1]; 
 
    printf("Finding possible keys...\n"); 
    for (  a = 1; a < 26; a++) { 
        for ( b = 0; b < 26; b++) { 
            if (decryptChar(mostFrequent, a, b) == mostFrequent && 
                decryptChar(secondMostFrequent, a, b) == secondMostFrequent) { 
                printf("Possible key found: a = %d, b = %d\n", a, b); 
            } 
        } 
    } 
 
    return 0; 
} 
