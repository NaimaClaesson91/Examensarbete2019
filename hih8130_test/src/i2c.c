#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "i2c.h"

void i2c_init(void) {

    TWBR = 12;
    TWCR |= (1 << TWEN);
}


inline void i2c_start() {

    TWCR |= (1 << TWINT) | (1 << TWSTA);
    while (!(TWCR & (1 << TWINT)))
    {
        ;
    }
}


inline void i2c_stop() {

    TWCR |= (1 << TWINT) | (1 << TWSTO);
}



inline void i2c_addr(uint8_t address, uint8_t rw) {

    TWDR = (address << 1) + rw;
    TWCR |= (1 << TWINT);
    TWCR &= ~(1 << TWSTA);
    while (!(TWCR & (1 << TWINT)))
    {
        ;
    }
}



inline uint8_t i2c_read_ACK(void) {

    TWCR |= ((1 << TWINT) | (1 << TWEA));
    while (!(TWCR & (1 << TWINT)))
    {
        ;
    }

    return TWDR;
}


inline uint8_t i2c_read_NAK(void) {

    TWCR &= ~(1 << TWEA);
    TWCR |= (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
    {
        ;
    }

    return TWDR;
}


void read_sensor(uint8_t * humHigh, uint8_t * humLow, uint8_t * tempHigh, uint8_t * tempLow) {

    i2c_start();
    i2c_addr(0x27, I2C_W);
    i2c_stop();
    _delay_ms(100);

    i2c_start();
    i2c_addr(0x27, I2C_R);
    *humHigh = i2c_read_ACK();
    *humLow = i2c_read_ACK();
    *tempHigh = i2c_read_ACK();
    *tempLow = i2c_read_NAK();
    i2c_stop();
    
}
