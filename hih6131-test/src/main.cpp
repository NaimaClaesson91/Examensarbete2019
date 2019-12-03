#include <Arduino.h>
#include <Wire.h>

uint8_t address = 0x27;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
}

void loop()
{
    Wire.beginTransmission(address);
    Wire.endTransmission();
    delay(100); 

    Wire.requestFrom(address, 4);

    uint8_t humidity_h = Wire.read();
    uint8_t humidity_l = Wire.read();
    uint8_t temp_h = Wire.read();
    uint8_t temp_l = Wire.read();

    Wire.endTransmission();

    Serial.println("Humidity_H: " + String(humidity_h));
    Serial.println("Humidity_L: " + String(humidity_l));
    Serial.println("Temp_H: " + String(temp_h));
    Serial.println("Temp_L: " + String(temp_l));
    Serial.print("\n");

    delay(5000);
}