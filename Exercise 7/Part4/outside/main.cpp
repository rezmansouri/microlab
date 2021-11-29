#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"
#include "keypad.h"

static unsigned char password[5] = "8642";
static unsigned char password_input[4];
static bool signed_in = false;

bool comparePassword()
{
    for (int i = 0; i < 4; i++)
    {
        if (password[i] != password_input[i])
        {
            return false;
        }
    }
    return true;
}

int main(void)
{

    unsigned char input;
    unsigned char char_count = 0;

    LCD_Init();
    keypad_init();
    LCD_String("password:");

    DDRD = 0x00;
    UART_init(9600);

    while (1)
    {
        input = key_scan();

        if (input != 255)
        {

            if (signed_in)
            {
                if (input != '*')
                {
                    LCD_Char(input);
                }
                UART_TxChar(input);
            }
            else
            {
                LCD_Char(input);
                password_input[char_count++] = input;
                if (char_count == 4)
                {
                    char_count = 0;
                    if (comparePassword())
                    {
                        PORTA |= 0x08;
                        _delay_ms(1000);
                        signed_in = true;
                        LCD_Clear();
                        LCD_String("steps:");
                    }
                    else
                    {
                        PORTA |= 0x10;
                        _delay_ms(1000);
                        LCD_Clear();
                        LCD_String("password:");
                    }
                    PORTA &= 0x07;
                }
            }
        }
    }
    return 0;
}