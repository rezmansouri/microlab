## Part 1
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

## Part 2
### Task:

Following Part 1 of the exercise, connect a push button on `PIND2` (_originally PINA0_) and 7 more LEDs on `PORTC`. Write a program to blink these LEDs in 0.5 intervals when a logical change on `PIND2` is occured. Use the **external clock frequency** to maintain the intervals.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part2/circuit.gif"/>
</p>

The program for [Part1](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part1/main.cpp) is expanded to support external interrupt requests on `INT0` along with the circuit of 8 LEDs.

We need an indicator for knowing whether the LEDs should blink or not.

`static bool blink_active = true;`

Further, if an interrupt request is received on `INT0` (_PIND2 is triggered_) this indicator must be flipped. Hence, the following routine seems to do the job.

```
ISR(INT0_vect)
{
    blink_active = !blink_active;
}
```

`blink_active` is set as `true` initially, because when the microcontroller starts, a logical change will be occured on `PIND2`, flipping it to `false` and disabling all the LEDs, as desired.

In order to use `INT0` requests properly, the following registers must be configured in the `main()` function initially.

```
GICR = 1 << INT0; // Enable External INT0
MCUCR = 1 << ISC00; // ISC00 = 1 & ISC01 = 0 for any logical change on INT0 to request an interrupt
```

## Part 3
### Task:

Following Part 2 of the exercise, write a program that once `PIND2` is trigerred (_originally PINA0_) these 8 LEDs blink consecutively in 0.5 second intervals, and do the same thing in reverse until they all turn off. Use the **external clock frequency** to maintain the intervals.

### Explanation for the proposed solution:

![circuit](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part3/circuit.gif)

The program for [Part2](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part2/main.cpp) is expanded to support consecutive blinking of the LEDs.

To begin with, We need a variable to store the index of the LED which is going to turn on next.

`static int LED_turn = 0;`

Moreover, we also need a variable to store the direction of the LEDs blinking.

`static bool reverse = false;`

And finally, the thrust of this part of the exercise, is the function below. This function is called everytime the `TIMER0` indicates 0.5 intervals (*AND INT0 is triggered formerly*). It increments/decrements the `LED_turn` based on the direction of the blinking `reverse`. Once the LED_turn had reached the `-1` value, we know that the show is finished, thus all the variables participating in this procedure are reset and the wait for another `INT0` external interrupt begins.

```
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
```
*This function is called everytime the `TIMER0` indicates 0.5 intervals (AND INT0 is triggered formerly)*:
```
ISR(TIMER0_OVF_vect) // interrupt routine for timer 0 overflow
{
    ...
    if (blink_active)
    {
        blink(); // blinking PORTC LEDs
    }
    ...
}
```


#### References

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).

This [article](https://www.electronicwings.com/avr-atmega/atmega1632-external-hardware-interrupts) explaining how to config `INT0` interrupts.

This <a href="http://mcuhq.com/21/how-to-create-a-blinking-led-project-using-atmega16-microcontroller-in-proteus-step-by-step-with-pictures" target="_blank">article</a> explaining how to use an external clock source in proteus.