#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

int main(void)
{

    DDRD = 0xff;  //setting the data direction of port D as output to send the message
    DDRC = 0x00; //setting the port C data direction as input to get send flags from the reader

    //the 200 character string to be sent
    char message[] = "Test: Kharazmi University (Danushgah-e Xuarezmi) is a major public research university in Iran, named after Khwarizmi (780-850c), Persian mathematician and geographer offering a wide range of studies";

    eeprom_busy_wait();                  //waiting for EEPROM to get ready
    eeprom_write_block(message, 0, 200); //writing the message as a block of bytes into EEPROM

    char read_message[200];                  //the message to be read
    eeprom_read_block(read_message, 0, 200); //reading a block of bytes from EEPROM and assigning it to read_message

    for (int i = 0; i < 200; i++) //for each character in the message, a pulse will be sent on port D
    {
        while (PINC == 0x00);
        PORTD = read_message[i];
        _delay_ms(1);
    }

    while (1);

    return 0;
}