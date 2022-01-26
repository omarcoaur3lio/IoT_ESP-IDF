#include "sys.h"
#include "lcd.h"


unsigned char count = 0;
unsigned char lcd_init(void);

unsigned char lcd_init(void) {
    printf("lcd_init()\n");

    Soma();

    return 0;
}

unsigned char lcd_write(unsigned int value) {
    printf("lcd = %d\n", value);
    return 0;
}

unsigned char lcd_read_count(void) {
    return count;
}