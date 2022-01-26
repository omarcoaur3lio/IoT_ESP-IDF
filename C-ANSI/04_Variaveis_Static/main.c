#include <stdio.h>

unsigned int returnAuto(void) {
    unsigned int x = 0;
    x++;
    x++;
    return x;
}
unsigned int returnStatic(void) {
    static unsigned int y = 0;
    y++;
    y++;
    return y;
}

int main (void) {
    printf("X: %d\n", returnAuto());
    printf("X: %d\n", returnAuto());
    // A variavel static mantem o valor do ultimo retorno
    printf("Y: %d\n", returnStatic());
    printf("Y: %d\n", returnStatic());
}