### Task:

Following the [First](https://github.com/rezmansouri/microlab/tree/main/Exercise%203/Part1) part of the exercise, connect four one-digit 7 Segments to a microcontroller (to the same port), and using timer/counter 1, write a program to count from 0...9999 such that the displays toggle on/off so fast that it wouldn't seem like it to the human eye!

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%203/Part2/circuit.gif"/>
</p>

_The tricky part of this question, is the limitation of the displays being on the same port;_ 
Hence, Using `PORTD[0..3]` pins, we have to indicate which display to turn on at each moment.

Just like the first part, we have the digits array, along with the following variables:

```
static char digits[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

static int index_4 = 0;
static int index_3 = 0;
static int index_2 = 0;
static int index_1 = 0;

static char flag_1 = 0x01;
static char flag_2 = 0x02;
static char flag_3 = 0x04;
static char flag_4 = 0x08;

static char turn = 4;
```

The `index_i` variables, for each 7-Seg, indicate which digit to be chosen for, from the `digits` array.

The `flag_i` variables, for each 7-Seg, indicate their common port to be set as high on `PORTD`;

The `turn` variable, tells the microcontroller which 7-Seg to turn on at each moment.

The interrupt service routine for the timer/counter 1 needs to be modified as follows:

```
ISR(TIMER1_OVF_vect) // interrupt routine for timer 1 overflow
{
    if (turn == 4)
    {
        PORTC = digits[index_4];
        PORTD = flag_4;
        turn = 3;
    }
    else if (turn == 3)
    {
        PORTC = digits[index_3];
        PORTD = flag_3;
        turn = 2;
    }
    else if (turn == 2)
    {
        PORTC = digits[index_2];
        PORTD = flag_2;
        turn = 1;
    }
    else if (turn == 1)
    {
        PORTC = digits[index_1];
        PORTD = flag_1;
        turn = 4;
        increment();
    }
    TCNT1 = 64500;
}
```

I believe it's clear what I'm doing up there, the only thing left is the `increment()` method.

```
void increment(void)
{
    if (index_4 == 9 && index_3 == 9 && index_2 == 9 && index_1 == 9) // setting the display to 0000
    {
        index_4 = 0;
        index_3 = 0;
        index_2 = 0;
        index_1 = 0;
        return;
    }
    if (index_4 == 9)
    {
        index_4 = 0;
        index_3++;
        return;
    }
    if (index_3 == 9)
    {
        index_3 = 0;
        index_2++;
    }
    if (index_2 == 9)
    {
        index_2 = 0;
        index_1++;
    }
    index_4++;
}
```