#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdio.h>

#include "gpio.h"
#include "uart.h"

void sleep(void);

ISR(PCINT2_vect)
{
    gpio_led_on();
}

int main(void)
{
    gpio_init();
    uart_init();

    gpio_led_on();
    _delay_ms(5000);

    while(1)
    {
        gpio_led_off();
        gpio_sleep();
        sleep();
        _delay_ms(5000);
    }

    return 0;
}

void sleep(void)
{
    // Disable global interrupts.
    cli();

    // Disable the ADC.
    ADCSRA &= ~(1 << ADEN);

    // Disable UART RX and TX.
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));

    // Enable pin change interrupt on PCINT16 (PD0/UART RX).
    PCMSK2 |= (1 << PCINT16);
    PCIFR  |= bit (PCIF2);
    PCICR |= (1 << PCIE2);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_adc_disable();
    power_spi_disable();
    power_twi_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();

    // Turn off Brown-Out Detection.
    MCUCR |= ((1 << BODS) | (1 << BODSE));
    MCUCR |= (1 << BODS);

    sleep_enable();
    sei();
    sleep_cpu();
    // Sleeping.



    // Waking up.
    cli();

    // Disable pin change interrupt 2 (RX-pin).
    PCICR &= ~(1 << PCIE2);
    PCMSK2 &= ~(1 << PCINT16);

    sleep_disable();
    power_twi_enable();
    power_adc_enable();


    // Enable UART RX and TX.
    UCSR0B |= ((1 << RXEN0) | (1 << TXEN0));
}

