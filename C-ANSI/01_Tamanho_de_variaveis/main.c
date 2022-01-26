#include <stdio.h>

int main (void) {
    
    // Tipos básicos em C
    unsigned char a;
    unsigned int b;
    float c;
    double d;
    long double e;

    printf("\nTamanho dos tipos basicos em C \n");
    printf("CHAR %d \n", sizeof(a));
    printf("INT %d \n", sizeof(b));
    printf("FLOAT %d \n", sizeof(c));
    printf("DOUBLE %d \n", sizeof(d));
    printf("LONG DOUBLE %d \n", sizeof(e));
    printf("\n------------------------------------\n");

    // Modificadores de tipo em C
    unsigned int f;
    unsigned short int g;
    unsigned long int h;
    unsigned long long int i;

    printf("\nTamanho dos tipos basicos em C (com modificadores) \n");
    printf("INT %d \n", sizeof(f));
    printf("SHORT INT %d \n", sizeof(g));
    printf("LONG INT %d \n", sizeof(h));
    printf("LONG LONG INT %d \n", sizeof(i));
    printf("\n------------------------------------\n");

    return 0;
}