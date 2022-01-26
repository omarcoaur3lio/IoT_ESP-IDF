#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed int int32_t;
typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

BOOL compare(char * str1, char * str2) {
    if (strcmp(str1, str2) == 0) { // strcmp returns 0 if the strings are equal
        return TRUE;
    } else {
        return FALSE;
    }
}

int32_t main(void) {
    if (compare("HELLO", "HELLo") == TRUE) {
        printf("São iguais\n");
    } else {
        printf("São diferentes\n");
    }
    return 0;
}