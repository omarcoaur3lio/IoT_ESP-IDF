#include <stdio.h>

int main(void) {
    // Não é possível alterar um ponteiro
    // const char * dummy = "HELLO";
    // *dummy = 'A';

    // Alocação em RAM (permite sua modificação)
    char dummy[] = "HELLO";
    dummy[0] = 'A';
    printf("%s", dummy);
    return 0;
}