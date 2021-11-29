## Part 1:
### Task:

Interface a 3x4 keypad with the microcontroller, along with an lcd to display the keys pressed.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part1/circuit.gif"/>
</p>

_I hope I find enough time later to explain how I wrote this but lmk if you have questions._

## Part 2:
### Task:

Following [Part 1](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part1) modify your program such that when a predefined password is inserted, a green LED blinks, otherwise a red one blinks.

_note that the original task was to develop a program that users could be registered with username/passwords and then the authentication part must've been written. but I couldn't have finished that in time._

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part2/circuit.gif"/>
</p>

## Part 3:
### Task:

Interface a bipolar stepper motor and using microcontroller's UART feature, send the number of steps through the simulator's virutal terminal, making the stepper motor move.

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

## Part 4:
### Task:

Following [Part 3](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part3), modify your circuit and program, such that it works jointly with the circuit and the program from [Part 2](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part2); Only this time, after logging in, the number of steps for the stepper motor, is received from another microcontroller.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part4/circuit.gif"/>
</p>

Suppose we have a server room (_the inside_) which has the stepper motor. The outside of the server room, controls the stepper motor inside, after logging in.

**The number of steps are sent after the * key is pressed**

_I hope I find enough time later to explain how I implemented this_

## Part 5:
### Task:

Following [Part 4](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part4), modify your circuit and program, such that it works jointly with the circuit and the program from [Part 4](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part4); Only this time, an LM35 temprature sensor is connected to the inside part, and the inside microcontroller sends the temprature read to outside using its usart feature.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part5/circuit.gif"/>
</p>

Now the server room is complete! it has a temprature sensor as well.

**The number of steps are sent after the * key is pressed**

_I hope I find enough time later to explain how I implemented this_

#### References

The `keypad.h` library was gathered from [here](https://microlearn.ir/1185/p_keypad.html) and modified, (it was _buggy!_).

The `lcd.h` library was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The `uart.h` library was gathered from [this article](https://www.electronicwings.com/avr-atmega/atmega1632-usart).