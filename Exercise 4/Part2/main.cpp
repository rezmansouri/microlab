#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

short second = 55;
short minute = 59;
short hour = 15;
short ante_meridiem_hour;
char display_content[33];
char am_pm[3];
static int timer_2_overflow_count = 0;

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