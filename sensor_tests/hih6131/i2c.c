#include <avr/io.h>
#include <util/delay.h>

#include "i2c.h"

void i2c_init(void)
{
    // Power the sensor through GPIO.
    DDRC |= (1 << DDC3);

    // 200 kHz SCL clock frequency.
    TWBR = 12;

    // Enable the I2C interface.
    TWCR |= (1 << TWEN);
}

inline void i2c_start()
{
    TWCR |= (1 << TWINT) | (1 << TWSTA);
    while (!(TWCR & (1 << TWINT)))
    {
    }
}


inline void i2c_stop()
{
    TWCR |= (1 << TWINT) | (1 << TWSTO);
}



inline void i2c_addr(uint8_t address, uint8_t rw)
{
    TWDR = (address << 1) + rw;
    TWCR |= (1 << TWINT);
    TWCR &= ~(1 << TWSTA);
    while (!(TWCR & (1 << TWINT)))
    {
    }
}



inline uint8_t i2c_read_ACK(void)
{
    TWCR |= ((1 << TWINT) | (1 << TWEA));
    while (!(TWCR & (1 << TWINT)))
    {
    }

    return TWDR;
}


inline uint8_t i2c_read_NAK(void)
{
    TWCR &= ~(1 << TWEA);
    TWCR |= (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
    {
    }

    return TWDR;
}

void i2c_read_hih6131(uint8_t * humHigh, uint8_t * humLow, uint8_t * tempHigh, uint8_t * tempLow)
{
    // Turn on the sensor.
    PORTC |= (1 << PORTC3);

    // Send measurement request.
    i2c_start();
    i2c_addr(I2C_HIH6131_ADDR, I2C_W);
    i2c_stop();

    // Wait for the measurement to get done.
    _delay_ms(I2C_START_UP_TIME);

    // Fetch the humidity and temperature data.
    i2c_start();
    i2c_addr(I2C_HIH6131_ADDR, I2C_R);
    *humHigh = i2c_read_ACK();
    *humLow = i2c_read_ACK();
    *tempHigh = i2c_read_ACK();
    *tempLow = i2c_read_NAK();
    i2c_stop();

    // Turn off the sensor.
    PORTC &= ~(1 << PORTC3);
}

