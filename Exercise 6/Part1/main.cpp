#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

static int timer_0_overflow_count = 0;
static char lcd_content[15];
static float temp;

ISR(TIMER0_OVF_vect)
{
    if (timer_0_overflow_count == 488)
    {
        ADCSRA |= _BV(ADSC);              // start the conversion
        while ((ADCSRA & _BV(ADIF)) == 0) // waiting for conversion finish interrupt flag
            ;
        temp = ADCW * 0.488;
        sprintf(lcd_content, " temperature= %02d", (int)temp);
        LCD_Clear();
        LCD_String(lcd_content);
        timer_0_overflow_count = 0;
    }
    else
    {
        timer_0_overflow_count++;
    }
    TCNT0 = 72;
}

int main(void)
{
    DDRA &= ~0x01;   // Setting Data Direction of ADC0 as input
    ADCSRA = 0x87; // Enabling ADC with 128 scaling
    ADMUX = 0x40;  // Setting the reference voltage as AVCC

    TCCR0 = _BV(CS01);   // prescaler = clk / 8
    TIMSK |= _BV(TOIE0); // unmasking timer 0 overflow interrupt
    TCNT0 = 72;

    LCD_Init();

    sei(); // enabling interrupts

    while (1)
        ;
    return 0;
}