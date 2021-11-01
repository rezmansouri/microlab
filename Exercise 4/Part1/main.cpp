#include <avr/io.h>
#include "lcd.h"

int main(void)
{
    LCD_Init();
    LCD_String("Hello World!");
    while (1);
    return 0;
}