#include <avr/io.h>

#include "gpio.h"

void gpio_init(void)
{
    // Status LED.
    DDRD |= (1 << DDD5);
    gpio_led_off();
}

void gpio_led_on(void)
{
    PORTD |= (1 << PORTD5);
}

void gpio_led_off(void)
{
    PORTD &= ~(1 << PORTD5);
    DDRD &= ~(1 << DDD5);
}

void gpio_sleep(void)
{
    DDRB = 0x00;
    PORTB = 0x00;
    DDRC = 0x00;
    PORTC = 0x00;
    DDRD = 0x00;
    PORTD = 0x00;
}
