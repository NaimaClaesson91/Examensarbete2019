#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "i2c.h"
#include "adc.h"
#include "rn2483.h"
#include "gpio.h"
#include "snooze.h"
#include "credentials.h"


ISR(PCINT2_vect)
{
    gpio_led_on();

}



int main(void)
{
  gpio_led_on();
  _delay_ms(3000); //modem start up time
  gpio_led_off();

  //UCSR0B &= ~(1 << RXEN0); // 
  uart_init();
  i2c_init();
  adc_init();
  gpio_init();



  loraData_t loraData;


  char hweui[DEV_EUI_LENGTH];
  const char * app_eui = _APP_EUI;
  const char * app_key = _APP_KEY;

  //_delay_ms(1000);

  rn2483_auto_baud();
  _delay_ms(1000);

  rn2483_get_hweui(hweui);

  rn2483_set_freq();
  rn2483_join_otaa(hweui, app_eui, app_key);

    while (1) 
    {

        _delay_ms(100);
        read_sensor(&loraData.humHigh, &loraData.humLow, &loraData.tempHigh, &loraData.tempLow);
        adc_battery_sim(&loraData.battStatusHigh, &loraData.battStatusLow);

        rn2483_transmit_unconfirmed_package(&loraData);

        gpio_led_off();
        rn2483_sleep("900000"); // 15 min transmit intervall
        _delay_ms(10);
        snooze_sleep();

        i2c_init();

    }
}