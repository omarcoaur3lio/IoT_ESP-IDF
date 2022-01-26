#include <stdio.h>
// Protótipo de funções  
unsigned char Soma(unsigned char x, unsigned char z);
unsigned int SomaMaiores(unsigned char x, unsigned char z);


unsigned int SomaMaiores(unsigned char x, unsigned char z) {
    return x + z;
}

int main (void) {
    unsigned char result;
    unsigned int resultMaiores;
    result = Soma(200, 55);
    resultMaiores = SomaMaiores(200, 77);
    printf("\n %d \n", result);
    printf("\n %d \n", resultMaiores);
    
    return 0;
}

unsigned char Soma(unsigned char x, unsigned char z) {
    return x + z;
}