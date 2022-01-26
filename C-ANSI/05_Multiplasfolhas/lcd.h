#ifndef __LCD_H__
#define __LCD_H__

#include "calc.h"

unsigned char lcd_init(void);
unsigned char lcd_write(unsigned int value);
unsigned char lcd_read_count(void);

#endif