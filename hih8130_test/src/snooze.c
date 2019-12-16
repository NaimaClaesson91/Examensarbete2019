#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdio.h>

#include "gpio.h"
#include "uart.h"


void snooze_sleep(void)
{
    // Disable global interrupts.
    cli();

    // Disable the ADC.
    ADCSRA &= ~(1 << ADEN);

    // Enable pin change interrupt on PCINT16 (PD0/UART RX).
    PCMSK2 |= (1 << PCINT16);

    // Enable pin change interrupt 2 (PCINT 23 to 16).
    PCICR |= (1 << PCIE2);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_twi_disable();
    power_timer2_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_spi_disable();
    power_adc_disable();

    // Disable UART RX and TX.
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));
    DDRD &= ~(1 << DDD1);
    PORTD |= (1 << PD1);

    sleep_enable();
    sei();
    sleep_cpu();
    // Sleeping...
    cli();

    // Disable pin change interrupt 2 (PCINT 23 to 16).
    PCICR &= ~(1 << PCIE2);
    PCMSK2 &= ~(1 << PCINT16);

    // Waking up when detecting RX activity.
    sleep_disable();
    power_all_enable();
    ADCSRA |= (1 << ADEN);


    // Enable UART RX and TX.
    UCSR0B |= ((1 << RXEN0) | (1 << TXEN0));

}


void snooze_shut_down(){
        // Disable global interrupts.
    cli();

    // Disable the ADC.
    ADCSRA &= ~(1 << ADEN);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_twi_disable();
    power_timer2_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_spi_disable();
    power_adc_disable();

    // Disable UART RX and TX.
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));
    DDRD &= ~(1 << DDD1);
    PORTD |= (1 << PD1);

    sleep_enable();

    sleep_cpu();
    // Sleeping...
}