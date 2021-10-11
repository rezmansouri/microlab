#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "uart.h"

int main(void)
{

    DDRD = 0xff;  //setting the data direction of port D as output to send the message

    //the 200 character string to be sent
    char message[] = "Test: Kharazmi University (Danushgah-e Xuarezmi) is a major public research university in Iran, named after Khwarizmi (780-850c), Persian mathematician and geographer offering a wide range of studies";

    eeprom_busy_wait();                  //waiting for EEPROM to get ready
    eeprom_write_block(message, 0, 200); //writing the message as a block of bytes into EEPROM

    char read_message[200];                  //the message to be read
    eeprom_read_block(read_message, 0, 200); //reading a block of bytes from EEPROM and assigning it to read_message

	UART_init(9600); //initialize UART with 9600 baud rate
    for (int i = 0; i < 200; i++)
    {
        UART_TxChar(read_message[i]);
    }

    while (1);

    return 0;
}