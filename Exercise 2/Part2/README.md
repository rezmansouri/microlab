### Task:

Following Part 1 of the exercise, connect a push button on `PIND2` (_originally PINA0_) and 7 more LEDs on `PORTC`. Write a program to blink these LEDs in 0.5 intervals when a logical change on `PIND2` is occured. Use the **external clock frequency** to maintain the intervals.

### Explanation for the proposed solution:

![circuit](https://github.com/rezmansouri/microlab/blob/main/Exercise%202/Part2/circuit.gif)

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

`blink_active` is set as `true` initially, because when the micocontroller starts, a logical change will be occured on `PIND2`, flipping it to `false` and disabling all the LEDs, as desired.

In order to use `INT0` requests properly, the following registers must be configured in the `main()` function initially.

```
GICR = 1 << INT0; // Enable External INT0
MCUCR = 1 << ISC00; // ISC00 = 1 & ISC01 = 0 for any logical change on INT0 to request an interrupt
```

#### References

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).
This [article](https://www.electronicwings.com/avr-atmega/atmega1632-external-hardware-interrupts) explaining how to config INT0 interrupts.
