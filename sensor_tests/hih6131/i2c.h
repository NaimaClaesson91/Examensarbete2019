#ifndef _I2C_H_
#define _I2C_H_

#define I2C_R	            1
#define I2C_W	            0
#define I2C_HIH6131_ADDR    0x27
#define I2C_START_UP_TIME   60


void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

void i2c_addr(uint8_t address, uint8_t rw);

uint8_t i2c_read_ACK(void);
uint8_t i2c_read_NAK(void);

void i2c_read_hih6131(uint8_t * humHigh, uint8_t * humLow, uint8_t * tempHigh,
                      uint8_t * tempLow);

#endif // _I2C_H_
