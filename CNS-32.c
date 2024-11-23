#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

unsigned long mod_exp(unsigned long m, unsigned long e, unsigned long n) {
    unsigned long result = 1;
    m = m % n;

    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * m) % n;
        }
        e = e >> 1;
        m = (m * m) % n;
    }
    return result;
}

void generate_rsa_signature(unsigned long message, unsigned long private_key, unsigned long n, unsigned long *signature) {
    *signature = mod_exp(message, private_key, n);
}

unsigned long generate_random_k() {
    return rand() % 100;
}

void generate_dsa_signature(unsigned long message, unsigned long private_key, unsigned long p, unsigned long q, unsigned long *r, unsigned long *s) {
    unsigned long k = generate_random_k();
    *r = mod_exp(k, 2, q);
    *s = (private_key * *r + k * message) % q;
}

int main() {
    unsigned long message = 12345678;

    unsigned long rsa_n = 3233;
    unsigned long rsa_private_key = 2753;
    unsigned long rsa_signature = 0;

    unsigned long dsa_p = 23;
    unsigned long dsa_q = 11;
    unsigned long dsa_private_key = 6;
    unsigned long dsa_r = 0, dsa_s = 0;

    generate_rsa_signature(message, rsa_private_key, rsa_n, &rsa_signature);
    printf("RSA Signature: %lu\n", rsa_signature);

    generate_dsa_signature(message, dsa_private_key, dsa_p, dsa_q, &dsa_r, &dsa_s);
    printf("DSA Signature (1st time): r = %lu, s = %lu\n", dsa_r, dsa_s);

    generate_dsa_signature(message, dsa_private_key, dsa_p, dsa_q, &dsa_r, &dsa_s);
    printf("DSA Signature (2nd time): r = %lu, s = %lu\n", dsa_r, dsa_s);

    return 0;
}

