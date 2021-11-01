### Task:

Following [Part 2](https://github.com/rezmansouri/microlab/blob/main/Exercise%204/Part2) add an alarm clock to your RTC using timer/counter 1 and an LED.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%204/Part3/circuit.gif"/>
</p>

The buttons to set the alarm, send an external interrupt to the microcontroller on the positive edge, therefore, the micro should be able to what command was sent to it during the interrupt. The interrupt routine is as follows.

```
ISR(INT0_vect)
{
    if ((ALARM_CONTROL_PIN & (1 << 0)) == 1)
    {
        alarm_active = !alarm_active;
        if (alarm_active)
        {
            seconds_left = (alarm_hour - hour) * 3600 + (alarm_minute - minute) * 60 - second;
            alarm_triggered = false;
            sprintf(alarm_on_off, " ALARM ON");
        }
        else
        {
            sprintf(alarm_on_off, " ALARM OFF");
        }
        PORTA &= 0b11110111;
    }
    {
        if ((ALARM_CONTROL_PIN & (1 << 1)) == 2)
            alarm_hour++;
        if (alarm_hour == 24)
        {
            alarm_hour = 0;
        }
    }
    if ((ALARM_CONTROL_PIN & (1 << 2)) == 4)
    {
        alarm_hour--;
        if (alarm_hour == -1)
        {
            alarm_hour = 24;
        }
    }
    if ((ALARM_CONTROL_PIN & (1 << 3)) == 8)
    {
        alarm_minute++;
        if (alarm_minute == 60)
        {
            alarm_minute = 0;
        }
    }
    if ((ALARM_CONTROL_PIN & (1 << 4)) == 16)
    {
        alarm_minute--;
        if (alarm_minute == -1)
        {
            alarm_minute = 59;
        }
    }
    if (alarm_active)
    {
        sprintf(alarm_on_off, " ALARM ON");
    }
    else
    {
        sprintf(alarm_on_off, " ALARM OFF");
    }
    sprintf(alarm_content, "%s %02d:%02d", alarm_on_off, alarm_hour, alarm_minute);
}
```

Moreover, to use the timer/counter 1, its ISR should be implemented as something like this:

```
ISR(TIMER1_OVF_vect)
{
    timer_1_overflow_count++;
    if (timer_1_overflow_count == 15)
    {
        timer_1_overflow_count = 0;
        if (alarm_active && !alarm_triggered)
        {
            seconds_left--;
            if (seconds_left == 0)
            {
                PORTA |= 0b00001000;
                sprintf(alarm_content, " ALARM TRIGGERED");
                alarm_triggered = true;
            }
        }
    }
    TCNT1 = 16960;
}
```

#### References

The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

This [article](https://www.electronicwings.com/avr-atmega/atmega1632-external-hardware-interrupts) explaining how to config `INT0` interrupts.

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).