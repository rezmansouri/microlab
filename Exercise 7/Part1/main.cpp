#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "keypad.h"

int main(void)
{
    unsigned char input;

    LCD_Init();
    keypad_init();

    while (1)
    {
        input = key_scan();
        if (input != 255)
        {
            LCD_Char(input);
        }
    }
    return 0;
}