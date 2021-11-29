#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "uart.h"

static char steps[] = {0b00000100, 0b00000010, 0b00001000, 0b000000001};
static int lab_input_index = 0;
static int step_index = 0;

static int timer_0_overflow_count = 0;
static char message[2];
static float temp;

ISR(TIMER0_OVF_vect)
{
    if (timer_0_overflow_count == 244)
    {
        ADCSRA |= _BV(ADSC);              // start the conversion
        while ((ADCSRA & _BV(ADIF)) == 0) // waiting for conversion finish interrupt flag
            ;
        temp = ADCW * 0.488;
        sprintf(message, "%02d", (int)temp);
        timer_0_overflow_count = 0;
        for (int i = 0; i < 2; i++) {
            UART_TxChar(message[i]);
        }
    }
    else
    {
        timer_0_overflow_count++;
    }
    TCNT0 = 36;
}

void move_motor(int number_of_steps)
{
    for (int i = 0; i < number_of_steps; i++)
    {
        _delay_ms(700);
        if (step_index == 4)
            step_index = 0;
        PORTB = steps[step_index++];
    }
}

int main(void)
{
    char lab_input[10]; //the message from terminal
    DDRD = 0x00;             //setting the data direction of port D 0 as input to receive the message
    DDRB = 0x0F;
    UART_init(9600); //initialize UART with 9600 baud rate

    DDRA &= ~0x01; // Setting Data Direction of ADC0 as input
    ADCSRA = 0x87; // Enabling ADC with 128 scaling
    ADMUX = 0x40;  // Setting the reference voltage as AVCC

    TCCR0 = _BV(CS01);   // prescaler = clk / 8
    TIMSK |= _BV(TOIE0); // unmasking timer 0 overflow interrupt
    TCNT0 = 36;

    sei();

    char c;
    while (1)
    {
        c = UART_RxChar();
        if (c == '*')
        {
            move_motor(atoi(lab_input));
        }
        else
        {
            lab_input[lab_input_index++] = c;
        }
    }
    return 0;
}