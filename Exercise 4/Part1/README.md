### Task:

Write a program to print the famous `"Hello World"` on an LCD. 

### Explanation for the proposed solution:

<p align="center">
  <img src="https://github.com/rezmansouri/microlab/blob/main/Exercise%204/Part1/circuit.gif"/>
</p>

The program is self-explanatory:

```
#include <avr/io.h>
#include "lcd.h"

int main(void)
{
    LCD_Init();
    LCD_String("Hello World!");
    while (1);
    return 0;
}
```

#### References

The `lcd.h` was gathered using [this article](https://www.electronicwings.com/avr-atmega/lcd16x2-interfacing-with-atmega16-32).