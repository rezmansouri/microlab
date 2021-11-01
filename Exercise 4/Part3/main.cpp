#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"
#include "keypad.h"
#define ALARM_CONTROL_PIN PINC
#define ALARM_CONTROL_DDR DDRC

char second = 40;
char minute = 57;
char hour = 21;
char ante_meridiem_hour;
char display_content[15];
char am_pm[3];
static int timer_2_overflow_count = 0;

static char alarm_hour = 19;
static char alarm_minute = 56;
char alarm_on_off[8];
char alarm_content[15];
bool alarm_active = false;
static int timer_1_overflow_count = 0;

static int seconds_left;
bool alarm_triggered = false;

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
        LCD_Command(0xC0);
        LCD_String(alarm_content);
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

    TCCR2 = (1 << CS21);   // prescaler = clk / 8
    TIMSK |= (1 << TOIE2); // unmasking timer 2 overflow interrupt
    TCNT2 = 72;

    GICR = 1 << INT0;                    // Enable External INT1
    MCUCR = (1 << ISC00) | (1 << ISC01); // ISC00 = 1 & ISC01 = 0 for rising edge on INT0 to request an interrupt

    TCCR1A = 0x00;
    TCCR1B = (1 << CS10);  // prescaler = clk / 8
    TIMSK |= (1 << TOIE1); //unmasking timer 2 overflow interrupt
    TCNT1 = 16960;

    sei(); // enabling interrupts

    ALARM_CONTROL_DDR = 0x00;
    ALARM_CONTROL_PIN = 0x00;

    while (1)
        ;
    return 0;
}