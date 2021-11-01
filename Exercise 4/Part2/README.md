### Task:

Using **Timer 2** and an LCD, implement a digital real time clock.

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%204/Part2/circuit.gif"/>
</p>

Firstly, we need three variables to indicate the time:

```
short second = 0;
short minute = 0;
short hour = 0;
```

Moreover, a `short ante_meridiem_hour;` variable would help us display _AM/PM_ format of the time. Also, the variables `display_content` and `am_pm` will be holding the generated strings later.

And finally, we need `timer_2_overflow_count` to maintain the timer 2 overflows to measure a second pass.

In the interrupt routine of the timer 2, the time to be displayed is incremented each second and the LCD content is generated as well.

```
ISR(TIMER2_OVF_vect)
{
    if (timer_2_overflow_count == 488)
    {
        second++;
        if (second == 60)
        {
            second = 0;
            minute++;
        }
        if (minute == 60)
        {
            minute = 0;
            hour++;
        }
        if (hour == 24)
        {
            hour = 0;
        }
        if (hour < 12)
        {
            sprintf(am_pm, "AM");
        }
        else
        {
            sprintf(am_pm, "PM");
        }
        ante_meridiem_hour = hour <= 12 ? hour : (hour - 12);
        sprintf(display_content, "  %02d:%02d:%02d  %s", ante_meridiem_hour, minute, second, am_pm);
        LCD_Clear();
        LCD_String(display_content);
        timer_2_overflow_count = 0;
    }
    else
    {
        timer_2_overflow_count++;
    }
    TCNT2 = 72;
}
```

And in the main (_not really_) function, the configuration for the timer 2 is done and nothing else.

```
int main(void)
{
    LCD_Init();

    TCCR2 = (1 << CS21);  // prescaler = clk / 8
    TIMSK = (1 << TOIE2); // unmasking timer 2 overflow interrupt
    TCNT2 = 72;

    sei(); // enabling interrupts
    while (1)
        ;
    return 0;
}
```

#### References

The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The official [ATMEGA16 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/doc2466.pdf).