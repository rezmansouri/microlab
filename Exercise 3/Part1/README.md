### Task:

Using Timer/Counter 1 and a common 7 Segment, write a program to display the digits `0...9` consecutively on the 7 Segment. 

### Explanation for the proposed solution:

![circuit](https://github.com/rezmansouri/microlab/blob/main/Exercise%203/Part1/circuit.gif)

First, we need to declare the digits chronologically to be displayed on the 7 Segment, followed by an index to indicate which digits will be displayed next.

```
static char digits[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
                        // 0,    1,    2,    3,    4,    5,    6,    7,    8,    9
static int index = 1;
```

Secondly, an interrupt service routine needs to be implemented for timer 1 overflow event. In this routine, the required actions for the task - such as resetting the timer/counter, resetting the digit index - will be taken.

```
ISR(TIMER1_OVF_vect) // interrupt routine for timer 1 overflow
{
    if (index == 10)
        index = 0;         //reseting the digit index
    PORTD = digits[index]; // displaying the digit on the 7 segment
    index++;               // incrementing the digit index
    TCNT1 = 63974;         // reseting the timer value
}
```

And most importantly, the configuaration of the timer/counter 1 is done in the main function.

```
    TCNT1 = 63974; //initial value of the timer
    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); // Timer mode with 1024 prescler
    TIMSK = (1 << TOIE1);               // Unmasking time 1 overflow interrupt
```

Finally, the data direction of `PORTD` is set, along with displaying the digit `0` on the 7 Segment for the beginning.

```
    DDRD = 0xff; // Setting PORTD data direction as output
    PORTD = 0xc0; // Displaying the digit 0, initially
```

#### References

The official [Common 7 Segment Datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf) By WayJun Technology.

This [article](https://exploreembedded.com/wiki/AVR_Timer_Interrupts) explaining how to config Timer/Counter 1 registers.