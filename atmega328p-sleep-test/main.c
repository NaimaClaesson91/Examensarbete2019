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

    sleep_enable();
    sei();
    sleep_cpu();
    // Sleeping...

    // Waking up when detecting RX activity.
    sleep_disable();
    power_all_enable();

    // Disable pin change interrupt 2 (PCINT 23 to 16).
    PCICR &= ~(1 << PCIE2);

    // Enable UART RX and TX.
    UCSR0B |= ((1 << RXEN0) | (1 << TXEN0));
}

