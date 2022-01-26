#include <stdio.h>

unsigned int count = 50;
extern char text[]; // Acesso a variavel definida em outro arquivo

unsigned char lcd_init(void) {
    text[0] = 'A';
    printf("lcd_init()\n");
    return 0;
}

unsigned char lcd_write(unsigned int value) {
    printf("lcd_write(%d)\n", value + count);
    return 0;
}