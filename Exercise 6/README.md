## Part1
### Task:

Interface a LM35 temperature sensor with ATMEGA16 along with an LCD that displays the temperature. Use microcontroller's ADC feature.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%206/Part1/circuit.gif"/>
</p>

ATMEGA16 has a 10 bit inbuild ADC, that is, ranging from 0 to 1024 and 1023 steps. For this exercise the reference voltage is 5V which is supported through AVCC pin. Therefore, one degree change is equivalent to a 5V/1023 = 4.88mV voltage change.

Further, LM35's voltage/degree step is 10mV. Accordingly the resulted voltage change needs to be divised by 10, resulting in a final **0.488** division for the word read by the ADC: `temp = ADCW * 0.488;`

## Part2
### Task:

Following [Part 1](https://github.com/rezmansouri/microlab/blob/main/Exercise%206/Part1) modify your design and program such that a hysteresis is obtained and an stepper motor starts working if the temperature reaches the hysteresis. The hysteresis value must be modifiable. 

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%206/Part2/circuit.gif"/>
</p>

The same approach is taken for the conversion. The only notable difference is that in order to know whether to activate the motor or not, we need to check the condition right after reading the temperature: `motor_active = temp >= hysteresis;`

And in an ISR for the timer 2, this condition is always checked:

```
ISR(TIMER2_OVF_vect)
{
    if (timer_2_overflow_count == 146)
    {
        if (motor_active)
        {
            PORTA = steps[step_index++];
            if (step_index == 4)
            {
                step_index = 0;
            }
        }
        timer_2_overflow_count = 0;
    }
    else
    {
        timer_2_overflow_count++;
    }
    TCNT2 = 124;
}
```

Interfacing a bipolar stepper motor is implemented in [Exercise 5](https://github.com/rezmansouri/microlab/blob/main/Exercise%205).


#### References

This [article](https://exploreembedded.com/wiki/AVR_Timer_Interrupts) explaining how to config Timer/Counter 0 registers.

This [article](https://www.electronicwings.com/avr-atmega/atmega1632-adc) explaining how to config and use ADC.

The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).

The official [LM35 datasheet](https://www.ti.com/lit/ds/symlink/lm35.pdf).