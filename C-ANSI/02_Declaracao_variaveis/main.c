#include <stdio.h>

// Só retornará corretamente somas até o valor 255
unsigned char Soma(unsigned char x, unsigned char z) {
    return x + z;
}

// Retornará valores acima de 255
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