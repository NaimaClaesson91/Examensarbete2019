#include <avr/io.h>

#include "gpio.h"

// TODO: Enable internal pull-ups on unconnected pins.

void gpio_init(void)
{
    // Status LED.
    DDRD |= (1 << DDD2);
    gpio_led_off();
}

void gpio_led_on(void)
{
    PORTD |= (1 << PORTD2);
}

void gpio_led_off(void)
{
    PORTD &= ~(1 << PORTD2);
}

