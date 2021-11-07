### Task:

Interface a bipolar stepper motor with the microcontroller such that when an active-low push button on `PC2` is pressed, the motor starts rotating and stops when the button is not pressed. Use timer/counter 0 to maintain the motor command intervals.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%205/Part1/circuit.gif"/>
</p>

The stepper motor takes the following inputs as steps for a full 360 deg rotation:

`static char steps[] = {0b00001001, 0b00001010, 0b00000110, 0b00000101};`

Another variable to hold the current step and distinguish the next one is required:

`static int step_index = 0;`

And finally, the interrupt service routine for timer/counter 0 which contains the major portion of the program along with its overflow indicator:

```
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
```

In the main method, the timer/counter 0 and related interrupts are configured as follows:
```
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
```

#### References

This [article](https://exploreembedded.com/wiki/AVR_Timer_Interrupts) explaining how to config Timer/Counter 0 registers.

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).