# Test programs for the sensor
A collection of programs that is used to test separate parts of the sensor during assembly.

### Battery voltage
Enables the voltage divider for 500 μs and takes a ADC measurement every 5 seconds and print it on the UART.
```
Battery voltage = (ADC_VALUE/310.303) * 1.216
```

### Blinky
Blinks the LED (0.5 Hz) on the board to ensure that the microcontroller is running.

### HIH6131
Turns on the sensor and takes a temperature and humidity measurement over the I2C bus, and then print the result on the UART.
```
Temperature = ((TEMP_VALUE/16382) * 165) - 14
Humidity = (HUM_VALUE/16382) * 100
```

### RN2483
Python program that is used for easy testing of the LoRa modem.

### Sleep
Sleeps the ATmega328p to see how low sleep current can be achieved.
