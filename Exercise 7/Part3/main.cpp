#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"

static char steps[] = {0b00000100, 0b00000010, 0b00001000, 0b000000001};
static int terminal_input_index = 0;
static int step_index = 0;

void move_motor(int number_of_steps)
{
    for (int i = 0; i < number_of_steps; i++)
    {
        _delay_ms(700);
        if (step_index == 4)
            step_index = 0;
        PORTA = steps[step_index++];
    }
}

int main(void)
{
    char terminal_input[10]; //the message from terminal
    DDRD = 0x00;             //setting the data direction of port D 0 as input to receive the message
    DDRA = 0x0F;
    UART_init(9600); //initialize UART with 9600 baud rate

    char c;
    while (1)
    {
        c = UART_RxChar();
        if (c == 13)
        {
            move_motor(atoi(terminal_input));
        }
        else
        {
            terminal_input[terminal_input_index++] = c;
        }
    }
    return 0;
}