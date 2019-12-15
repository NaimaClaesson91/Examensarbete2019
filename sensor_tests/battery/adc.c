#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"


void adc_init()
{
    // MOSFET on PORTC0 are used for enabling the voltage divider.
    DDRC |= (1 << DDC0);
    PORTC &= ~(1 << PORTC0);

    // Connect pin ADC1 to the ADC.
    ADMUX |= (1 << MUX0);

    // Use AVcc as voltage reference.
    ADMUX |= (1 << REFS0);

    // Use 125 kHz sample rate.
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1));

    // Enable the ADC.
    ADCSRA |= (1 << ADEN);
}


void adc_battery(uint8_t * voltageHigh, uint8_t * voltageLow)
{
    // Turn on the voltage divider for 500 usec.
    PORTC |= (1 << PC0);
    _delay_us(500);
    PORTC &= ~(1 << PC0);

    // Start the analog to digital conversion.
    ADCSRA |= (1 << ADSC);

    // Wait until the ADC conversion is complete.
    while (!(ADCSRA & (1 << ADIF)))
    {
    }

    // Clear the ADC conversion complete flag.
    ADCSRA |= (1 << ADIF);

    // Save the result of the ADC conversion.
    *voltageLow = ADCL;
    *voltageHigh = ADCH;
}
