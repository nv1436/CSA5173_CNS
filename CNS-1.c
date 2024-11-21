#include <stdio.h> 
#include <string.h> 
void caesarEncrypt(char text[], int key) {
    int i; 
    int len = strlen(text); 
 
    for (i = 0; i < len; i++) { 
        if (text[i] >= 'A' && text[i] <= 'Z') { 
            text[i] = (text[i] - 'A' + key) % 26 + 'A'; 
        } 
        else if (text[i] >= 'a' && text[i] <= 'z') { 
            text[i] = (text[i] - 'a' + key) % 26 + 'a'; 
        } 
    } 
} 
int main() { 
    char message[100]; 
    int key; 
    printf("Enter a message: "); 
    fgets(message, sizeof(message), stdin); 
 
    printf("Enter the key (0-25): "); 
    scanf("%d", &key); 
 
    if (key < 0 || key > 25) { 
        printf("Invalid key! Please enter a key between 0 and 25.\n"); 
        return 1; 
    } 
    size_t length = strlen(message); 
    if (length > 0 && message[length - 1] == '\n') { 
        message[length - 1] = '\0'; 
    } 
    caesarEncrypt(message, key); 
    printf("Encrypted message: %s\n", message); 
    return 0; 
} 
