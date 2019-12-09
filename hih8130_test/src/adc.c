#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"


void adc_init(){

    ADMUX |= (1 << REFS0) | (1 << MUX0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADIE);

}


uint16_t adc_battery_sim(){

    uint16_t adc_value;

    adc_value = ADCL | ADCH << 8;
    ADCSRA |= (1 << ADSC);

    return adc_value;
}