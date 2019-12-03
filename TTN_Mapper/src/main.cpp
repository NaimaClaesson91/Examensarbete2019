#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 6, TXPin = 5;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buttonPin = 8;
int buttonState = 0;

void displayInfo() {

  Serial.print(F("Location: ")); 
  if (gps.location.isValid()) {

    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {

    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));

  if (gps.date.isValid()) {

    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {

    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));

  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));

    Serial.print(gps.time.hour());
    Serial.print(F(":"));

    if (gps.time.minute() < 10) Serial.print(F("0"));

    Serial.print(gps.time.minute());
    Serial.print(F(":"));

    if (gps.time.second() < 10) Serial.print(F("0"));

    Serial.print(gps.time.second());
    Serial.print(F("."));

    if (gps.time.centisecond() < 10) Serial.print(F("0"));

    Serial.print(gps.time.centisecond());
  } else {

    Serial.print(F("INVALID"));

  }

  Serial.println();
}

 void checkButton(int buttonState) {

  if (buttonState == LOW) { 
    return;

    } else if (buttonState == HIGH){

      lcd.print ("BUTTON PRESSED!");
      Serial.println("BUTTON WAS PRESSED!");
    
    }  
  }

 
 void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); 
  lcd.begin(16,2); 
  ss.begin(GPSBaud);
}

void loop() {

  lcd.clear();
  //buttonState = digitalRead(buttonPin);
  //checkButton(buttonState); 
  lcd.print("READY");
  delay(1000);

  while (ss.available() > 0){

    if (gps.encode(ss.read())) {

        displayInfo();
        delay(1000);
    }  

  if (millis() > 5000 && gps.charsProcessed() < 10) {

    Serial.println(F("No GPS detected: check wiring."));
    while(true);

  }
 }


}

