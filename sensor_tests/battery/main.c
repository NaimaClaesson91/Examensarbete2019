#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "serial.h"
#include "adc.h"

typedef struct
{
    uint8_t voltageHigh;
    uint8_t voltageLow;
} data_t;

int main(void)
{
    data_t data;

    uart_init();
    adc_init();

    for (;;)
    {
        char string[20];
        uint16_t voltage = 0;

        adc_battery(&data.voltageHigh, &data.voltageLow);
        voltage = (data.voltageHigh << 8) + (data.voltageLow);

        sprintf(string, "Voltage: %d\r\n", voltage);
        uart_print(string);

        _delay_ms(5000);
    }
}
