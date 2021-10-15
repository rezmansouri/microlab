#include <avr/io.h>
#include <avr/interrupt.h>

static int overflow_count = 0;

ISR(TIMER0_OVF_vect) // interrupt routine for timer 0 overflow
{
    TCNT0 = 36;       // reseting the timer value
    overflow_count++; // incrementing the overflow counter
    if (overflow_count == 244)
    /*
        with 1MHz frequency, 
        prescaler of 8, 
        and remainder tick of 36,  
        the timer overflows 244 times each 0.5 seconds
    */
    {
        PORTC ^= 0x01;      // blinking PORTC0 LED
        overflow_count = 0; // reseting the overflow counter
    }
}

int main(void)
{
    TCCR0 = (1 << CS01); // prescaler = clk / 8
    TCNT0 = 36;          // remainder timer ticks

    TIMSK = (1 << TOIE0); // unmasking timer 0 overflow interrupt

    DDRC = 0x01; // setting the data direction of PORTC0 as output

    sei(); // enabling interrupts

    while (1);
}