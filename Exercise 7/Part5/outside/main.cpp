#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"
#include "keypad.h"

static unsigned char password[5] = "8642";
static unsigned char password_input[4];
static bool signed_in = false;
static char temprature[2];

static char lcd_line_one[16];
static char lcd_line_two[16];

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

    sprintf(lcd_line_one, "password:");
    LCD_String_xy(0, 0, lcd_line_one);

    DDRD = 0x00;
    UART_init(9600);

    while (1)
    {

        if (signed_in)
        {
            for (int i = 1; i >= 0; i--)
            {
                temprature[i] = UART_RxChar();
            }
            sprintf(lcd_line_two, "temprature: %d", atoi(temprature));
            LCD_String_xy(1, 0, lcd_line_two);
        }

        input = key_scan();

        if (input != 255)
        {
            if (input != '*')
            {
                sprintf(lcd_line_one, "%s%c", lcd_line_one, input);
                LCD_String_xy(0, 0, lcd_line_one);
            }
            if (signed_in)
            {
                UART_TxChar(input);
            }
            else
            {
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
                        sprintf(lcd_line_one, "steps:");
                        LCD_String_xy(0, 0, lcd_line_one);
                    }
                    else
                    {
                        PORTA |= 0x10;
                        _delay_ms(1000);
                        LCD_Clear();
                        sprintf(lcd_line_one, "password:");
                        LCD_String_xy(0, 0, lcd_line_one);
                    }
                    PORTA &= 0x07;
                }
            }
        }
    }
    return 0;
}