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

#### References

The `keypad.h` library was gathered from [here](https://microlearn.ir/1185/p_keypad.html) and modified, (it was _buggy!_).

The `lcd.h` library was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).
