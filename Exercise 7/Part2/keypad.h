#include <util/delay.h>

#define KEY_PORT PORTD
#define KEY_DDR DDRD
#define KEY_PIN PIND

unsigned char table[13] = {
    '*', '0', '#',
    '7', '8', '9',
    '4', '5', '6',
    '1', '2', '3'};

void keypad_init(void)
{
    KEY_DDR = 0x0f;
    KEY_PORT = 0xff;
}

unsigned char key_released(void)
{
    KEY_PORT = 0x70;
    _delay_ms(3);
    if ((KEY_PIN & 0x70) == 0x70)
        return 1;
    else
        return 0;
}

unsigned char key_pressed(void)
{

    KEY_PORT = 0x70;
    _delay_ms(3);
    if ((KEY_PIN & 0x70) != 0x70)
    {
        _delay_ms(20);
        if ((KEY_PIN & 0x70) != 0x70)
            return 1;
    }
    return 0;
}

unsigned char key_scan(void)
{

    unsigned char i, key;
    if (key_pressed())
    {
        key = 0;
        for (i = 0; i < 4; i++)
        {
            KEY_PORT = ~(1 << i);
            _delay_ms(3);
            if ((KEY_PIN & 0x10) == 0x00)
                key = table[i * 3];
            else if ((KEY_PIN & 0x20) == 0x00)
                key = table[i * 3 + 1];
            else if ((KEY_PIN & 0x40) == 0x00)
                key = table[i * 3 + 2];
            else
                continue;
        }
        while (!key_released())
            ;
        return key;
    }
    else
        return 255;
}