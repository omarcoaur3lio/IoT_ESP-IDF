#include <stdio.h>
#include "lcd.h"

static unsigned int count = 50; // Variável com o escopo reduzido apenas ao main.
char text[200]; // Variável global para ser acessada com o extern

int main(void) {
    lcd_init();
    lcd_write(78 + count);
    return 0;
}