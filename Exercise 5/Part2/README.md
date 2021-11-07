### Task:

Following [Part 1](https://github.com/rezmansouri/microlab/blob/main/Exercise%205/Part1) modify your design and program such that the motors direction reverses everytime the push button is triggered.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%205/Part2/circuit.gif"/>
</p>

To know whether to increment the steps or decrement them, the `static int incrementor = 1;` is required;

And when the `step_index` needs to be changed, it'll be changed according to the `incrementor` and not the former `step_index++`;

```
...
            PORTA = steps[step_index];
            step_index += incrementor;
            if (step_index == 4)
            {
                step_index = 0;
            }
            if (step_index == -1)
            {
                step_index = 3;
            }
...
```

In order to capture the button being pressed, I used the external interrupt `INT0`, and implemented its ISR as follows:

```
ISR(INT0_vect)
{
    incrementor *= -1;
}
```

The `INT0` interrupt is configured as follows in the main method:

```
    GICR = 1 << INT0;                    // Enable External INT0
    MCUCR = (0 << ISC00) | (0 << ISC01); // ISC00 = 0 & ISC01 = 0 for falling edge on INT0 to request an interrupt
```

#### References

This [article](https://exploreembedded.com/wiki/AVR_Timer_Interrupts) explaining how to config Timer/Counter 0 registers.

This [article](https://www.electronicwings.com/avr-atmega/atmega1632-external-hardware-interrupts) explaining how to config `INT0` interrupts.

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).
