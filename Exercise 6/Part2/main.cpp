#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

static int timer_0_overflow_count = 0;
static char lcd_content[15];
static int temp;
static int hysteresis = 50;

static char steps[] = {0b00010000, 0b00001000, 0b00000100, 0b000000010};
static int step_index = 0;
static unsigned int timer_2_overflow_count = 0;
static bool motor_active = false;

ISR(TIMER0_OVF_vect)
{
    if (timer_0_overflow_count == 488)
    {
        ADCSRA |= _BV(ADSC);              // start the conversion
        while ((ADCSRA & _BV(ADIF)) == 0) // waiting for conversion finish interrupt flag
            ;
        temp = (int)(ADCW * 0.488);
        sprintf(lcd_content, " temperature= %02d", temp);
        LCD_Clear();
        LCD_String(lcd_content);
        LCD_Command(0xC0);
        sprintf(lcd_content, " hysteresis= %02d", hysteresis);
        LCD_String(lcd_content);
        motor_active = temp >= hysteresis;
        timer_0_overflow_count = 0;
    }
    else
    {
        timer_0_overflow_count++;
    }
    TCNT0 = 72;
}

ISR(TIMER2_OVF_vect)
{
    if (timer_2_overflow_count == 146)
    {
        if (motor_active)
        {
            PORTA = steps[step_index++];
            if (step_index == 4)
            {
                step_index = 0;
            }
        }
        timer_2_overflow_count = 0;
    }
    else
    {
        timer_2_overflow_count++;
    }
    TCNT2 = 124;
}

ISR(INT0_vect)
{
    if ((PIND >> 7) == 1)
    {
        hysteresis--;
    }
    else if ((PIND >> 6) == 1)
    {
        hysteresis++;
    }
}

int main(void)
{
    ADCSRA = 0x87; // Enabling ADC with 128 scaling
    ADMUX = 0x40;  // Setting the reference voltage as AVCC

    GICR = _BV(INT0);                // Enable External INT0
    MCUCR = _BV(ISC00) | _BV(ISC01); // ISC00 = 1 & ISC01 = 1 for rising edge on INT0 to request an interrupt

    TCCR0 = _BV(CS01);   // prescaler = clk / 8
    TIMSK |= _BV(TOIE0); // unmasking timer 0 overflow interrupt
    TCNT0 = 72;

    TCCR2 = _BV(CS21);   // prescaler = clk / 8
    TIMSK |= _BV(TOIE2); // unmasking timer 0 overflow interrupt
    TCNT2 = 124;

    DDRD = 0x00;

    DDRA = 0xFE;

    LCD_Init();

    sei(); // enabling interrupts

    while (1)
        ;
    return 0;
}