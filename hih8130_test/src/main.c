#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
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
  uint8_t battStatusHigh;
  uint8_t battStatusLow;

}loraData_t;


int main(void)
{

  uart_init();
  i2c_init();

  loraData_t loraData;

    while (1) 
    {
      read_sensor(&loraData.humHigh, &loraData.humLow, &loraData.tempHigh, &loraData.tempLow);
      printf("%d %d %d %d\n", loraData.humHigh, loraData.humLow, loraData.tempHigh, loraData.tempLow);

		   _delay_ms(2000);


    }
}
