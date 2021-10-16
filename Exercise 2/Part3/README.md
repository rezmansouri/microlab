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