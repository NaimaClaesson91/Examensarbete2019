#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>

#include "serial.h"
#include "i2c.h"
#include "adc.h"
#include "rn2483.h"


int main(void)
{

  uart_init();
  i2c_init();
  adc_init();

  loraData_t loraData;


  char hweui[DEV_EUI_LENGTH];
  const char * app_eui = "";
  const char * app_key ="";
  rn2483_auto_baud();
  _delay_ms(1000);

  rn2483_get_hweui(hweui);

  rn2483_set_freq();
  rn2483_join_otaa(hweui, app_eui, app_key);

  
  read_sensor(&loraData.humHigh, &loraData.humLow, &loraData.tempHigh, &loraData.tempLow);
  adc_battery_sim(&loraData.battStatusHigh, &loraData.battStatusLow);
  adc_battery_sim(&loraData.battStatusHigh, &loraData.battStatusLow);

  rn2483_transmit_unconfirmed_package(&loraData);

  

    while (1) 
    {


    }
}