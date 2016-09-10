/*
 * ALGORITHMS ARE FUN
 * Mingyang Zhang
 * 650242
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRLEN 256
#define MAXCHAR 2

bool is_prime(unsigned int n);

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    unsigned int size;

    /* Bertrand's postulate:
    For any n>1, there exists at least one prime p, s.t n<p<2n. */
    for(size = 2*n + 1; size < 4*n; size++){
        if(is_prime(size)){
            return size;
        }
    }

    exit(EXIT_FAILURE);
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    int i, count;
    unsigned char* str = malloc(MAXSTRLEN + 1);

    /* Initialize static rand array in universal_hash */
    srand(seed);
    universal_hash((unsigned char*)"", size);

    /* For output formatting requirement.
    Since the result is completely random,
    I might as well just print all MAXSTRLEN randnum */
    fprintf(stdout, "%d\n", MAXSTRLEN);
    srand(seed);
    for(i = 0; i < MAXSTRLEN; i++){
        fprintf(stdout, "%d\n", rand()%size);
    }

    /* Randomly append "0" or "1" */
    count = 0;
    strcpy((char*)str, "");
    for(i = 0; i < MAXSTRLEN; i++){
        if(rand()%2 == 0){
            strcat((char*)str, "0");
        } else{
            strcat((char*)str, "1");
        }
        if(universal_hash((unsigned char*)str, size) == 0){
            fprintf(stdout, "%s", (char*)str);
            fprintf(stdout, "\n");
            count++;
            if(count == n){
                return;
            }
        }
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
    /* x*r0 + y*r1 = k*size */
    unsigned int r0, r1;
    unsigned int x, y, k;
    char c0, c1;
    char s0[2], s1[2];
    unsigned char* str;
    int count = 0;

    srand(seed);
    r0 = rand()%size;
    r1 = rand()%size;

    /* Output formatting requirement */
    fprintf(stdout, "2\n");
    fprintf(stdout, "%d\n", r0);
    fprintf(stdout, "%d\n", r1);

    for(x = 32;; x++){
        for(y = 32;; y++){
            /* Looking for printable chars */
            if(((r0*x + r1*y)%size == 0) && (x<128 && y<128)){
                str = malloc(MAXCHAR + 1);
                strcpy((char*)str, "");
                /* int to char */
                c0 = x, c1 = y;
                /* Single char string */
                s0[0] = c0, s0[1] = '\0';
                s1[0] = c1, s1[1] = '\0';
                /* Append single char string to str */
                strcat((char*)str, s0);
                strcat((char*)str, s1);
                /* Output */
                fprintf(stdout, "%s", str);
                fprintf(stdout, "\n");
                free(str);
                count++;
                /* Check number of outputs */
                if(count >= n){
                    return;
                }
            }
        }
    }
}


/* ===========================================================
Function based on the work of Alistair Moffat:
http://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/isprime.c
============================================================ */
bool is_prime(unsigned int n){
    unsigned int divisor;
    bool isprime = true;

    for(divisor = 2; divisor*divisor <= n; divisor++){
        if(n%divisor == 0){
            isprime = false;
            return isprime;
        }
    }
    return isprime;
}
