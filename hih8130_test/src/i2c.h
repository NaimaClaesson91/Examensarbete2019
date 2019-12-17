#ifndef _I2C_H_
#define _I2C_H_

#define I2C_R	1
#define I2C_W	0


void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

void i2c_addr(uint8_t address, uint8_t rw);

uint8_t i2c_read_ACK(void);
uint8_t i2c_read_NAK(void);

void i2c_wait();

void read_sensor(uint8_t * hh, uint8_t * hl, uint8_t * th, uint8_t * tl);

#endif // _I2C_H_