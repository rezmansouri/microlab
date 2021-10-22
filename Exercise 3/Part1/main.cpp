#include <avr/io.h>
#include <avr/interrupt.h>

static char digits[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
                        // 0,    1,    2,    3,    4,    5,    6,    7,    8,    9
static int index = 1;

ISR(TIMER1_OVF_vect) // interrupt routine for timer 1 overflow
{
    if (index == 10)
        index = 0;         //reseting the digit index
    PORTD = digits[index]; // displaying the digit on the 7 segment
    index++;               // incrementing the digit index
    TCNT1 = 63974;         // reseting the timer value
}

int main(void)
{
    TCNT1 = 63974; //initial value of the timer

    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); // Timer mode with 1024 prescler
    TIMSK = (1 << TOIE1);               // Unmasking time 1 overflow interrupt

    sei();

    DDRD = 0xff; // Setting PORTD data direction as output
    PORTD = 0xc0; // Displaying the digit 0, initially

    while (1);
}