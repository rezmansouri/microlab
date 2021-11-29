### Task:

Following [Part 3](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part3), modify your circuit and program, such that it works jointly with the circuit and the program from [Part 2](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part2); Only this time, after logging in, the number of steps for the stepper motor, is received from another microcontroller.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part4/circuit.gif"/>
</p>

Suppose we have a server room (_the inside_) which has the stepper motor. The outside of the server room, controls the stepper motor inside, after logging in. 

**The number of steps are sent after the * key is pressed**

_I hope I find enough time later to explain how I implemented this_

#### References

The `keypad.h` library was gathered from [here](https://microlearn.ir/1185/p_keypad.html) and modified, (it was _buggy!_).

The `lcd.h` library was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The `uart.h` library was gathered from [this article](https://www.electronicwings.com/avr-atmega/atmega1632-usart).