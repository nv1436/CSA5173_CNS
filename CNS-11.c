#include <stdio.h> 
#include <string.h> 
unsigned long long factorial(int n) { 
if (n <= 1) 
return 1; 
return n * factorial(n - 1); 
} 
int main() { 
int keyLength = 25;  
    unsigned long long totalPossibleKeys = factorial(keyLength); 
 
    printf("Total possible keys (without considering identical encryption results): %llu\n", 
totalPossibleKeys); 
 
    unsigned long long effectivelyUniqueKeys = totalPossibleKeys / keyLength;  
 
    printf("Effectively unique keys (considering identical encryption results): %llu\n", 
effectivelyUniqueKeys); 
 
    return 0; 
} 
