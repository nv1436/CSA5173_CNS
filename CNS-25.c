#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int t = 0;
    int new_t = 1;
    int r = m;
    int new_r = a;
    
    while (new_r != 0) {
        int quotient = r / new_r;
        
        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
        
        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    
    if (r > 1) {
        printf("Inverse does not exist\n");
        return -1;
    }
    
    if (t < 0) {
        t = t + m;
    }
    
    return t;
}


void factor_n_using_common_factor(int n, int common_factor) {
    int other_factor = n / common_factor;
    printf("Found factor of n: %d\n", common_factor);
    printf("Other factor of n: %d\n", other_factor);
}


int main() {
    
    int n = 589;  
    int e = 7;    
    
    
    int C = 271;  
    

    int common_factor = gcd(C, n);  
    
    if (common_factor > 1) {
        printf("Common factor found: %d\n", common_factor);
        
        factor_n_using_common_factor(n, common_factor);
        

        int p = common_factor;
        int q = n / p;
        int phi_n = (p - 1) * (q - 1);
        printf("phi(n) = %d\n", phi_n);
        
        
        int d = mod_inverse(e, phi_n);
        if (d != -1) {
            printf("Private key d: %d\n", d);
        }
    } else {
        printf("No common factor found.\n");
    }
    
    return 0;
}

