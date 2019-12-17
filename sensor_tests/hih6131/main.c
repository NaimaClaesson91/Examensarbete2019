#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "serial.h"
#include "i2c.h"


typedef struct
{
    uint8_t humHigh;
    uint8_t humLow;
    uint8_t tempHigh;
    uint8_t tempLow;
} data_t;

int main(void)
{
    data_t data;

    uart_init();
    i2c_init();

    for (;;)
    {
        char string[30];
        uint16_t hum = 0;
        uint16_t temp = 0;

        i2c_read_hih6131(&data.humHigh, &data.humLow, &data.tempHigh, &data.tempLow);

        data.humHigh &= 0x3F;
        hum = (data.humHigh << 8) + data.humLow;
        temp = (data.tempHigh << 6) + (data.tempLow >> 2);

        sprintf(string, "Humidity: %d\r\nTemperature: %d\r\n", hum, temp);
        uart_print(string);

        _delay_ms(5000);
    }
}

