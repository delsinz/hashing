/*
 * ALGORITHMS ARE FUN
 * Mingyang Zhang
 * 650242
*/
#include "types.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Returns whether n1 is equal to n2 */
bool int_eq(long e1, long e2) {
    return e1 == e2;
}

/* Prints n to file */
void int_print(FILE *file, long e) {
    fprintf(file, " %ld", e);
}

/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2) {
    if(strcmp(str1, str2) == 0){
        return true;
    }
    return false;
}

/* Returns a copy of src */
char *str_copy(char *src) {
    char* dest = malloc(strlen(src) + 1);
    if(dest){
        strcpy(dest, src);
    } else{
        exit(EXIT_FAILURE);
    }
    return dest;
}

/* Prints str to file */
void str_print(FILE *file, char *str) {
    fprintf(file, "%s", str);
}
