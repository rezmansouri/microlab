### Task:

Interface a bipolar stepper motor and using microcontroller's UART feature, send the number of steps through the simulator's virutal terminal, making the stepper motor to move.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part3/circuit.gif"/>
</p>

I allow a 10 digit number to be received from the terminal:

`char terminal_input[10];`

After doing the initial configurations,

_Data Directions and initializing the uart with the prevalent 9600 baud rate_,

```
    DDRD = 0x00;
    DDRA = 0x0F;
    UART_init(9600);
```

The main loop would be as follows:

```
    char c;
    while (1)
    {
        c = UART_RxChar();
        if (c == 13)
        {
            move_motor(atoi(terminal_input));
        }
        else
        {
            terminal_input[terminal_input_index++] = c;
        }
    }
```

The `atoi()` function, converts the terminal input string to an integer.

#### References

The `uart.h` library was gathered from [this article](https://www.electronicwings.com/avr-atmega/atmega1632-usart).
