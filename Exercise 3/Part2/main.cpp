#include <avr/io.h>
#include <avr/interrupt.h>

static char digits[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

static int index_4 = 0;
static int index_3 = 0;
static int index_2 = 0;
static int index_1 = 0;

static char flag_1 = 0x01;
static char flag_2 = 0x02;
static char flag_3 = 0x04;
static char flag_4 = 0x08;

static char turn = 4;

void increment(void)
{
    if (index_4 == 9 && index_3 == 9 && index_2 == 9 && index_1 == 9) // setting the display to 0000
    {
        index_4 = 0;
        index_3 = 0;
        index_2 = 0;
        index_1 = 0;
        return;
    }
    if (index_4 == 9)
    {
        index_4 = 0;
        index_3++;
        return;
    }
    if (index_3 == 9)
    {
        index_3 = 0;
        index_2++;
    }
    if (index_2 == 9)
    {
        index_2 = 0;
        index_1++;
    }
    index_4++;
}

ISR(TIMER1_OVF_vect) // interrupt routine for timer 1 overflow
{
    if (turn == 4)
    {
        PORTC = digits[index_4];
        PORTD = flag_4;
        turn = 3;
    }
    else if (turn == 3)
    {
        PORTC = digits[index_3];
        PORTD = flag_3;
        turn = 2;
    }
    else if (turn == 2)
    {
        PORTC = digits[index_2];
        PORTD = flag_2;
        turn = 1;
    }
    else if (turn == 1)
    {
        PORTC = digits[index_1];
        PORTD = flag_1;
        turn = 4;
        increment();
    }
    TCNT1 = 64500;
}

int main(void)
{
    TCNT1 = 64500; //initial value of the timer

    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); // Timer mode with 1024 prescler
    TIMSK = (1 << TOIE1);               // Unmasking time 1 overflow interrupt

    sei();

    DDRC = 0xff;  // Setting PORTC data direction as output
    PORTC = 0xc0; // Displaying the digit 0, initially
    DDRD = 0x0f;  // Setting PORTD data direction as output to indicate which 7 Seg. to use

    while (1);
}