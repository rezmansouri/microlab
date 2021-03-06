#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"
#include "uart.h"

int main(void)
{
    char message[200]; //the message to be read
    DDRD = 0x00; //setting the data direction of port D as input to receive the message

    UART_init(9600); //initialize UART with 9600 baud rate
    for (int i = 0; i < 200; i++)
    {
        message[i] = UART_RxChar();
    }

    LCD_Init();
    for (int i = 0; i < 200;)
    {
        char first_line[16];
        for (int j = 0; j < 16 && i < 200; j++, i++)
        {
            first_line[j] = message[i];
        }
        LCD_Clear();
        LCD_String(first_line);
        LCD_Command(0xC0);
        char second_line[16];
        for (int j = 0; j < 16 && i < 200; j++, i++)
        {
            second_line[j] = message[i];
        }
        LCD_String(second_line);
        _delay_ms(50);
    }

    PORTB = 0x00;

    while (1);

    return 0;
}