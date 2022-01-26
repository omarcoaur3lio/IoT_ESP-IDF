#include "sys.h"
#include "lcd.h"

int main (void) {
    lcd_init();
    lcd_write(45);
    printf("Count = %d\n", lcd_read_count());
    return 0;
}