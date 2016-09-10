/*
 * ALGORITHMS ARE FUN
 * Mingyang Zhang
 * 650242
*/
#include "hash.h"

#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 256

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

/* Very simple hash */
unsigned int worst_hash(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

/* Basic numeric hash function */
unsigned int num_hash(long n, unsigned int size) {
    return n % size;
}

/* Bad hash function */
unsigned int bad_hash(char *key, unsigned int size) {
    static unsigned int called = 0;
    static unsigned int randnum;
    if(called == 0){
        randnum = rand()%size;
        called = 1;
    }
    return randnum*key[0] % size;
}

/* Universal hash function as described in Dasgupta et al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size) {
    unsigned int i, key_len = strlen((char*)key), sigma = 0;
    static unsigned int called = 0;
    static unsigned int randnum[MAXSTRLEN];

    if(called == 0){
        for(i = 0; i < MAXSTRLEN; i++){
            randnum[i] = rand()%size;
        }
        called = 1;
    }

    for(i = 0; i < key_len; i++){
        sigma += randnum[i]*key[i];
    }

    return sigma%size;
}
