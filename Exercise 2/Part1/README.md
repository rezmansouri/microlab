### Task:
Suppose the frequency of a crystal quartz connected to a micorcontroller, is 1 MHz. Write a program to invert `PORTC0` in 0.5 intervals. Use the **external clock frequency** to maintain the intervals.

### Explanation for the proposed solution:
![circuit](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part1/circuit.gif)
The task prompt asked me to *suppose* the external clock source, whereas I actually used a crystal quartz with prevalent configuation (1MHz frequency *as asked* and two 22pF capacitors). 

It's good to know that if **proteus 8** is used for simulation, in order to use an external clock source, the following config must be set for the microcontroller:

![circuit](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part1/microconfig.png)

In order to have *exactly* 0.5 second intervals in inverting the PORT, interrupts must be used. I used the 8 bit TIMER0 of ATMEGA16. 

The program counts timer overflows to reach 0.5 second intervals.

Using <a href="https://www.easycalculation.com/engineering/electrical/avr-timer-calculator.php" target="_blank">this</a> website, I calculated the required prescale and initial value of the timer to acquire the 0.5 second interval.

The clock frequency is 10^6 Hz, the required frequency is 2 Hz (0.5 second intervals). 

By devising the frequency by 8 (prescaler of 8),

`TCCR0 = (1 << CS01);`

And Initial value of 36 for the timer to reciprocate the remainder ticks after timer overflows.

`TCNT0 = 36;`

The timer overflows 244 times with additional 36 ticks, thus the following routine seems like to be appropriate:
```
static int overflow_count = 0;
ISR(TIMER0_OVF_vect) // interrupt routine for timer 0 overflow
{
    TCNT0 = 36;
    overflow_count++;
    if (overflow_count == 244) {
        PORTC ^= 0x01;      // blinking PORTC0 LED
        overflow_count = 0; // reseting the overflow counter
    }
}
```

#### References
The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).

This <a href="http://mcuhq.com/21/how-to-create-a-blinking-led-project-using-atmega16-microcontroller-in-proteus-step-by-step-with-pictures" target="_blank">article</a> explaining how to use an external clock source in proteus.