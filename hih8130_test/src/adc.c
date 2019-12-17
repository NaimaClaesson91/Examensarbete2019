#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"


void adc_init(){

    DDRC |= (1 << DDC0);
    PORTC &= ~(1 << PC0); //mosfet off
    ADMUX |= (1 << REFS0) | (1 << MUX0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

}


void adc_battery_sim(uint8_t * battStatusHigh, uint8_t * battStatusLow){

    PORTC |= (1 << PC0); // mosfet on
    _delay_us(500); // mosfet start-time
    PORTC &= ~(1 << PC0); // mosfet off

    ADCSRA |= (1 << ADSC);
    while(!(ADCSRA & (1 << ADIF))){

    }
    ADCSRA |= (1 << ADIF);
    *battStatusLow = ADCL;
    *battStatusHigh = ADCH;
}