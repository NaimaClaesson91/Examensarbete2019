#include <avr/io.h>

#include "gpio.h"

// TODO: Enable internal pull-ups on unconnected pins.

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
}