## Question 4:
### Task:
Suppose Two Microcontrollers. Save a 200 Character String in one's EEPROM and send it over to the other one,

using a port (all 8 pins). Receive the sent string on the other and print it on an LCD.

### Explanation for the proposed solution:
![screenshot](https://github.com/rezmansouri/microlab/blob/main/Exercise%201/Question4/screenshot.jpg)
Microcontroller *A* saves the 200 character string in its EEPROM and reads from it right after. Then in a 200 step `for` loop, waits

for a signal from a reader (`PORTD7`) stating that they are ready to receive, then sets an 8-bit character on its `PORTC`;

Microcontroller *B* states that it is not ready to read yet by setting its `PORTD` to `0` resulting in `PORTD7 = 0` as well.

Then in a 200 step `for` loop, sends signals for its readiness followed by storing the read character on `PORTC`. 

And Finally, Displays the read string on a `16x2LCD`.

#### References
The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).


## Question 5:
### Task:
Suppose Two Microcontrollers. Save a 200 Character String in one's EEPROM and send it over to the other one,

using a port (**only one pin** / **serial communication**). Receive the sent string on the other and print it on an LCD.

### Explanation for the proposed solution:
![screenshot](https://github.com/rezmansouri/microlab/blob/main/Exercise%201/Question5/screenshot.jpg)
Microcontroller *A* saves the 200 character string in its EEPROM and reads from it right after. Then in a 200 step `for` loop, transmits a character from the string using UART protocol on its `PORTD1` (`TDx`).

Microcontroller *B* in a 200 step `for` loop, receives the character on `PORTD0` (`RDx`). 

And Finally, Displays the read string on a `16x2LCD`.

#### References
The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).

The `uart.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/atmega1632-usart).