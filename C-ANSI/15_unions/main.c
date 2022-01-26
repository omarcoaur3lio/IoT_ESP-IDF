#include <stdio.h>
#include <stdlib.h>

union {
    unsigned char buff[2];
    unsigned short result;
} data;

unsigned char high = 0xAA;
unsigned char low = 0xBB;

int main(void) {
    /* O objetivo é ter o resultado 0XAABB */

    /*
    * Usando o operador bit a bit

    unsigned short result;
    result = ((high << 8) | low);
    printf("%X", result);

   */

    /* Usando union */
    data.buff[0] = low;
    data.buff[1] = high;
    printf("%X", data.result);

    return 0;
}