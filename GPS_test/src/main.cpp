#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 5); // RX, TX

void setup(){

  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop(){
  
  if (mySerial.available())
    Serial.write(mySerial.read());
    
  if (Serial.available())
    mySerial.write(Serial.read());
}