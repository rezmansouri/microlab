#include <avr/io.h>
#include <avr/interrupt.h>

static char steps[] = {0b00001001, 0b00001010, 0b00000110, 0b00000101};
static int step_index = 0;
static unsigned int overflow_count = 0;

ISR(TIMER0_OVF_vect) // interrupt routine for timer 0 overflow
{
    TCNT0 = 64; // reseting the timer value
    overflow_count++; // incrementing the overflow counter
    if (overflow_count == 781)
    {
        overflow_count = 0;
        if (PINC == 0)
        {
            PORTA = steps[step_index];
            step_index++;
            if (step_index == 4)
            {
                step_index = 0;
            }
        }
    }
}

int main(void)
{
    TCCR0 = (1 << CS01); // prescaler = clk / 8
    TCNT0 = 64;         // remainder timer ticks

    TIMSK = (1 << TOIE0); // unmasking timer 0 overflow interrupt

    DDRC = 0x00; // setting the data direction of PORTC0 as input
    DDRA = 0x0f; // setting the data direction of PORTA0 as output

    sei(); // enabling interrupts

    while (1);
    return 0;
}