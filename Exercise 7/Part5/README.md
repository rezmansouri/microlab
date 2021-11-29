### Task:

Following [Part 4](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part4), modify your circuit and program, such that it works jointly with the circuit and the program from [Part 4](https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part2); Only this time, an LM35 temprature sensor is connected to the inside part, and the inside microcontroller sends the temprature read to outside using its usart feature.

### Proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%207/Part5/circuit.gif"/>
</p>

Now the server room is complete! it has a temprature sensor as well.

_I hope I find enough time later to explain how I implemented this_

#### References

The `keypad.h` library was gathered from [here](https://microlearn.ir/1185/p_keypad.html) and modified, (it was _buggy!_).

The `lcd.h` library was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The `uart.h` library was gathered from [this article](https://www.electronicwings.com/avr-atmega/atmega1632-usart).