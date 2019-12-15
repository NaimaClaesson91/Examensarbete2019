#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << DDD5);
    PORTD &= ~(1 << PORTD5);

    while(1)
    {
        _delay_ms(1000);
        PORTD |= (1 << PORTD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PORTD5);
    }

    return 0;
}

