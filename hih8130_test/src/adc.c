#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"


void adc_init(){

    DDRC |= (1 << DDC0);
    ADMUX |= (1 << REFS0) | (1 << MUX0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2);// | (1 << ADIE);

}


void adc_battery_sim(uint8_t * battStatusHigh, uint8_t * battStatusLow){

    PORTC |= (1 << PC0); // mosfet on
    _delay_ms(10); // mosfet start-time
    *battStatusLow = ADCL;
    *battStatusHigh = ADCH;
    ADCSRA |= (1 << ADSC);
    PORTC &= ~(1 << PC0); // mosfet off
}