#include <avr/io.h>
#include <avr/interrupt.h>

static int overflow_count = 0;
static bool blink_active = true; // indicating whether the LEDs should blink or not
static int LED_turn = 0;
static bool reverse = false;

void blink(void)
{
    if (LED_turn == 7)
    {
        reverse = true;
    }
    else if (LED_turn == -1)
    {
        blink_active = false;
        reverse = false;
        LED_turn = 0;
        PORTC = 0x00;
        return;
    }
    PORTC = (1 << LED_turn);
    if (reverse) {
        LED_turn--;
    } else {
        LED_turn++;
    }
}

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
        if (blink_active)
        {
            blink(); // blinking PORTC LEDs
        }
        overflow_count = 0; // reseting the overflow counter
    }
}

ISR(INT0_vect) // interrupt routine for external requests on INT0 / PD2
{
    blink_active = true; // flipping the indicator
}

int main(void)
{
    TCCR0 = (1 << CS01); // prescaler = clk / 8
    TCNT0 = 36;          // remainder timer ticks

    TIMSK = (1 << TOIE0); // unmasking timer 0 overflow interrupt

    DDRC = 0xff; // setting the data direction of PORTC0 as output
    DDRD = 0x00; // setting the data direction of PORTD as input

    GICR = 1 << INT0;   // Enable External INT0
    MCUCR = 1 << ISC00; // ISC00 = 1 & ISC01 = 0 for any logical change on INT0 to request an interrupt

    sei();

    while (1);
}